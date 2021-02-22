#pragma once

#include <algorithm>
#include <assert.h>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <vector>

using ll = long long;

struct CacheConnection
{
    int server_id;
    int latency;
};

struct EndpointConnection
{
    int datacenter_latency;
    std::vector<CacheConnection> cache_connections;
};

struct Request
{
    int video_id;
    int endpoint_id;
    int amount_of_requests;
};

struct Config
{
    int videos_count;
    int endpoint_count;
    int request_count;
    int cache_servers_count;
    int cache_server_capacity;
    std::vector<int> video_sizes;
    std::vector<EndpointConnection> connections;
    std::vector<Request> requests;
};

Config parse(std::istream &in)
{
    Config config;

    in >> config.videos_count >> config.endpoint_count >> config.request_count >> config.cache_servers_count >> config.cache_server_capacity;

    config.video_sizes.resize(config.videos_count);
    for (auto i = 0; i < config.videos_count; ++i)
    {
        in >> config.video_sizes[i];
    }

    config.connections.resize(config.endpoint_count);
    for (auto i = 0; i < config.endpoint_count; ++i)
    {
        EndpointConnection connection;
        int cache_connections_count;

        in >> config.connections[i].datacenter_latency >> cache_connections_count;

        config.connections[i].cache_connections.resize(cache_connections_count);

        for (auto j = 0; j < cache_connections_count; ++j)
        {
            in >> config.connections[i].cache_connections[j].server_id >> config.connections[i].cache_connections[j].latency;
        }
    }

    config.requests.resize(config.request_count);
    for (auto i = 0; i < config.request_count; ++i)
    {
        in >> config.requests[i].video_id >> config.requests[i].endpoint_id >> config.requests[i].amount_of_requests;
    }

    return config;
}

struct CacheServer
{
    int server_id;
    int cap;
    std::set<int> videos_to_store;
};

struct Answer
{
    std::vector<CacheServer> servers;
};

class Creator
{
public:
    Creator(std::ostream &out, Config config) : out_(out), config(config)
    {
        for (int i = 0; i < config.cache_servers_count; ++i)
        {
            ans.servers.push_back(CacheServer{i, config.cache_server_capacity, std::set<int>()});
        }
    }

    bool AppropriateForVideo(int server_id, int video_id)
    {
        return ans.servers[server_id].cap >= config.video_sizes[video_id] &&
               ans.servers[server_id].videos_to_store.find(video_id) == ans.servers[server_id].videos_to_store.end();
    }

    void AddVideo(int server_id, int video_id)
    {
        auto &server = ans.servers[server_id];
        assert(server.cap >= config.video_sizes[video_id]);
        assert(server.videos_to_store.find(video_id) == server.videos_to_store.end());

        server.cap -= config.video_sizes[video_id];
        server.videos_to_store.insert(video_id);
    }

    void Print()
    {
        out_ << ans.servers.size() << std::endl;
        for (auto &server : ans.servers)
        {
            out_ << server.server_id << " ";
            for (auto &video : server.videos_to_store)
            {
                out_ << video << " ";
            }
            out_ << std::endl;
        }
    }

public:
    Answer ans;
    Config config;

private:
    std::ostream &out_;
};

long long judge(Config &data, Creator &creator)
{
    std::vector<std::unordered_set<int>> videos_in_servers;
    videos_in_servers.resize(data.cache_servers_count);

    for (auto server : creator.ans.servers)
    {
        for (auto video : server.videos_to_store)
        {
            videos_in_servers[server.server_id].emplace(video);
        }
    }

    std::vector<std::unordered_map<int, int>> cache_latencies;
    cache_latencies.resize(data.endpoint_count);

    ll min_latency = __LONG_LONG_MAX__;

    for (auto i = 0; i < data.endpoint_count; ++i)
    {
        for (auto latency : data.connections[i].cache_connections)
        {
            cache_latencies[i][latency.server_id] = latency.latency;

            if (latency.latency < min_latency)
            {
                min_latency = latency.latency;
            }
        }
    }

    ll score = 0;

    ll max_possible_score = 0;

    for (auto i = 0; i < data.request_count; ++i)
    {
        Request &current = data.requests[i];
        ll min_val = __LONG_LONG_MAX__;

        for (auto j = 0; j < data.cache_servers_count; ++j)
        {
            if (cache_latencies[current.endpoint_id].count(j) &&
                videos_in_servers[j].count(current.video_id) &&
                cache_latencies[current.endpoint_id][j] < min_val)
            {
                min_val = cache_latencies[current.endpoint_id][j];
            }
        }

        if (min_val == __LONG_LONG_MAX__)
        {
            max_possible_score += current.amount_of_requests * (data.connections[current.endpoint_id].datacenter_latency - min_latency);
            continue;
        }

        score += current.amount_of_requests * (data.connections[current.endpoint_id].datacenter_latency - min_val);
        max_possible_score += current.amount_of_requests * (data.connections[current.endpoint_id].datacenter_latency - min_latency);
    }

    ll amount_of_requests = 0;

    for (auto request : data.requests)
    {
        amount_of_requests += request.amount_of_requests;
    }

    score = (score * 1000) / amount_of_requests;
    max_possible_score = (max_possible_score * 1000) / amount_of_requests;

    // std::cout << "Max possible score:" << max_possible_score << std::endl;

    return score;
}
