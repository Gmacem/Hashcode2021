#pragma once

#include <algorithm>
#include <assert.h>
#include <iostream>
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

struct CacheServer {
    int server_id;
    int cap;
    std::set<int> videos_to_store;
};

struct Answer {
    std::vector<CacheServer> servers;
};

class Creator {
public:
    Creator(std::ostream &out, Config config) : out_(out), config(config) {
        for (int i = 0; i < config.cache_servers_count; ++i) {
            ans.servers.push_back(CacheServer{i, config.cache_server_capacity, std::set<int>()});
        }
    }

    void AddVideo(int server_id, int video_id) {
        auto& server = ans.servers[server_id];
        assert(server.cap >= config.video_sizes[video_id]);
        assert(server.videos_to_store.find(video_id) == server.videos_to_store.end());

        server.cap -= config.video_sizes[video_id];
        server.videos_to_store.insert(video_id);
    }

    void Print() {
        out_ << ans.servers.size() << std::endl;
        for (auto &server : ans.servers)
        {
            out_ << server.server_id << " ";
            for (auto &video : server.videos_to_store) {
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

long long judge(Creator &c)
{
    return 0;
}
