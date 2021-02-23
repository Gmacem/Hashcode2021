#include <deque>
#include <random>
#include "jenkins.h"

std::mt19937 mt_rand(time(0));

struct ScoringQueue
{
    void Push(long long value)
    {
        scores.push_back(value);

        if (scores.size() > kQueueSize)
        {
            scores.pop_front();
        }
    }

    void PushSame()
    {
        Push(scores.back());
    }

    long long GetLast()
    {
        return scores.back();
    }

    bool IsStagnating()
    {
        if (scores.size() < kQueueSize)
        {
            return false;
        }

        long long initial_value = scores.front();

        for (auto i = 1; i < scores.size(); ++i)
        {
            if (scores[i] != initial_value)
            {
                return false;
            }
        }

        return true;
    }

    std::deque<long long> scores;

    static constexpr int kQueueSize = 20;
};

struct AnswerMutator
{
    void MutateAnswer(Creator &creator)
    {
        std::uniform_int_distribution<int> distr(0, creator.ans.servers.size() - 1);
        bool success = false;

        for (auto i = 0; i < 1000 && !success; ++i)
        {
            int first_index = distr(mt_rand);
            int second_index = distr(mt_rand);

            if (first_index == second_index || creator.ans.servers[first_index].videos_to_store.empty() || creator.ans.servers[second_index].videos_to_store.empty())
            {
                continue;
            }

            int first_video_index = std::uniform_int_distribution<int>(0, creator.ans.servers[first_index].videos_to_store.size() - 1)(mt_rand);
            int second_video_index = std::uniform_int_distribution<int>(0, creator.ans.servers[second_index].videos_to_store.size() - 1)(mt_rand);

            auto first_elem_iter = creator.ans.servers[first_index].videos_to_store.begin();
            for (auto i = 0; i < first_video_index; ++i)
            {
                first_elem_iter++;
            }

            first_video_index = *(first_elem_iter);

            auto second_elem_iter = creator.ans.servers[second_index].videos_to_store.begin();
            for (auto i = 0; i < second_video_index; ++i)
            {
                second_elem_iter++;
            }

            second_video_index = *(second_elem_iter);

            first_index = creator.ans.servers[first_index].server_id;
            second_index = creator.ans.servers[second_index].server_id;

            if (first_video_index == second_video_index)
            {
                continue;
            }

            if (!creator.TryRemoveVideo(first_index, first_video_index))
            {
                continue;
            }

            if (!creator.TryRemoveVideo(second_index, second_video_index))
            {
                creator.AddVideo(first_index, first_video_index);
                continue;
            }

            if (!creator.TryAddVideo(first_index, second_video_index))
            {
                creator.AddVideo(first_index, first_video_index);
                creator.AddVideo(second_index, second_video_index);
                continue;
            }

            if (!creator.TryAddVideo(second_index, first_video_index))
            {
                creator.TryRemoveVideo(first_index, second_video_index);
                creator.AddVideo(first_index, first_video_index);
                creator.AddVideo(second_index, second_video_index);
                continue;
            }
            success = true;
        }
    }

    // void Unmutate(Creator &creator)
    // {
    //     creator.TryRemoveVideo(first_index, second_video_index);
    //     creator.TryRemoveVideo(second_index, first_video_index);
    //     creator.AddVideo(first_index, first_video_index);
    //     creator.AddVideo(second_index, second_video_index);
    // }

    int first_index;
    int second_index;
    int first_video_index;
    int second_video_index;
};