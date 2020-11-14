#include "lmb/thread_job.h"

#include "lmb/debug.h"

namespace LMB
{




void JobManager::ThreadExec(size_t thread_index)
{
    {
        std::lock_guard<std::mutex> lock(m_mutex);
    }

    m_threads_state[thread_index] = EThreadState::Executing;
    
    std::shared_ptr<Job> current_job = nullptr;

    int job_num=0;

    while(!m_end)
    {
        long num_jobs =0;
        
        //job selection 
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            num_jobs = m_jobs.size() - (long)m_job_start;

            if(num_jobs>0)
            {
                DEBUG_LOG("thread executing %d (%d).\n",m_job_start,m_jobs.size());
                m_threads_state[thread_index] = EThreadState::Executing;
                current_job = m_jobs[m_job_start];
                ++m_job_start;
            }
            else
            {
                m_threads_state[thread_index] = EThreadState::Waiting;
                m_cv.wait(lock);
                continue;
            }

        }

        if(current_job)
        {
            current_job->Execute();
            current_job->m_completed = true;
            current_job = nullptr;
        }
    }
    
    m_threads_state[thread_index] = EThreadState::Ended;
}

JobManager::JobManager()
{
    m_num_threads = std::thread::hardware_concurrency();
    //m_num_threads = 1;
    
    //printf("JobManager started\n");
    m_end = false;
    m_job_start=0;

    std::lock_guard<std::mutex> lock(m_mutex);

    for(int i=0;i<m_num_threads;i++)
    {
        m_threads_state.push_back(EThreadState::Waiting);
        m_threads.push_back(std::move(std::thread(&JobManager::ThreadExec,this,m_threads.size())));
    }
}

JobManager::~JobManager()
{
    End();
}



void JobManager::End()
{
    m_end = true;
    for(int i=0;i<m_threads.size();i++)
        if(m_threads[i].joinable())
            m_threads[i].join();
}



void JobManager::Push(std::shared_ptr<Job> job)
{
    std::unique_lock<std::mutex> jobs_lock(m_mutex);
    m_jobs.push_back(job);
    jobs_lock.unlock();

    for(int i=0;i<m_threads_state.size();i++)
    {
        if(m_threads_state[i] == EThreadState::Waiting)
        {
            m_cv.notify_one();
            return;
        }
    }
}



}