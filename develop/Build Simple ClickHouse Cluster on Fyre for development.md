# Build Simple ClickHouse Cluster on Fyre for development

## Background 

try to solve the issue: 
https://github.ibm.com/ClickHouse/release/issues/39


## applied 3 Fyre machines:

machines and software to be installed:

| machine | ip | software installed |
|---|---|---|
|ch-001|9.30.188.170|jdk, zookeeper, clickhouse|
|ch-002|9.30.230.135|jdk, zookeeper |
|ch-003|9.30.199.125|jdk, zookeeper, clickhouse|

vi /etc/hosts

9.30.188.170 ch-001   
9.30.230.135 ch-002  
9.30.199.125 ch-003

## 1. Install java: (on all 3 machines):
  ```
  sudo apt install openjdk-8-jdk
  ```

## 2. Install zookeeper

- Download zookeeper (on all 3 machines):

    ```
    sudo wget https://dlcdn.apache.org/zookeeper/zookeeper-3.7.0/apache-zookeeper-3.7.0-bin.tar.gz

    mkdir /data

    sudo tar -zxvf ./apache-zookeeper-3.7.0-bin.tar.gz -C /data

    cd /data

    ln -s apache-zookeeper-3.7.0-bin zookeeper
    ```

- Create data and log folder and make a copy of zoo.fg (on all 3 machines):
    ```
    cd /data/zookeeper

    mkdir data
    mkdir logs

    cp conf/zoo_sample.cfg conf/zoo.cfg
    ```

- Edit zoo.fg to config zookeeper (on all 3 machines):  

    ```
    tickTime=2000
    initLimit=10
    syncLimit=5
    dataDir=/data/zookeeper/data
    clientPort=2181
    server.1=9.30.188.170:2888:3888
    server.2=9.30.230.135:2888:3888
    server.3=9.30.199.125:2888:3888
    ```
- Set the id for each machine:   

    on the machine 9.30.188.170, run:    
    ```
    /data/zookeeper # echo 1 > /data/zookeeper/data/myid   
    ```
    on the machine 9.30.230.135, run:   
    ```
    /data/zookeeper # echo 2 > /data/zookeeper/data/myid  
    ```
    on the machine 9.30.199.125, run:   
    ```
    /data/zookeeper # echo 3 > /data/zookeeper/data/myid  
    ```

- Start zookeeper (on all 3 machines):
    ```
    ./bin/zkServer.sh start
    ```

- Check zookeeper status:  
    ```
    /data/zookeeper # ./bin/zkServer.sh status                                                                                                                                     root@squibber1
    /usr/bin/java
    ZooKeeper JMX enabled by default
    Using config: /data/zookeeper/bin/../conf/zoo.cfg
    Client port found: 2181. Client address: localhost. Client SSL: false.
    Mode: leader
    ```  
   

## 3. Setup ClickHouse cluster  
run on machine 9.30.188.170 and 9.30.199.125
- Install  ClickHouse 
    ```
    sudo apt-get install -y apt-transport-https ca-certificates dirmngr
    sudo apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv 8919F6BD2B48D754

    echo "deb https://packages.clickhouse.com/deb stable main" | sudo tee \
        /etc/apt/sources.list.d/clickhouse.list
    sudo apt-get update

    sudo apt-get install -y clickhouse-server clickhouse-client
    ```
use `/etc/clickhouse-server/config.xml`  
- Add listen host for accepting all  
    
    ```
    <!-- Default values - try listen localhost on IPv4 and IPv6. -->
    <!--
    <listen_host>::1</listen_host>
    <listen_host>127.0.0.1</listen_host>
    -->
    <listen_host>0.0.0.0</listen_host>          <---------------------------------- add 
    <!-- Don't exit if IPv6 or IPv4 networks are unavailable while trying to listen. -->
    <!-- <listen_try>0</listen_try> -->

    <!-- Allow multiple servers to listen on the same address:port. This is not recommended.
      -->
    <!-- <listen_reuse_port>0</listen_reuse_port> -->

    <!-- <listen_backlog>4096</listen_backlog> -->    
    ```

- Setup my one path :
    ```
    <!-- Path to data directory, with trailing slash. -->
    <path>/data/ClickHouse/</path>

    <!-- Path to temporary data for processing hard queries. -->
    <tmp_path>/data/ClickHouse/tmp/</tmp_path>    
    ```

- Add config for cluster:      
    set a cluster `groupby_test` with 1 shard 2 replica   
    
    ```
    <remote_servers>
        <groupby_test> <!-- cluster name self defined -->
            <shard> 
                <!-- Optional. Shard weight when writing data. Default: 1. -->
                <weight>1</weight>
                <!-- Optional. Whether to write data to just one of the replicas. Default: false (write data to all replicas). -->
                <internal_replication>true</internal_replication>
                <replica>  
                    <host>9.30.188.170</host>
                    <port>9000</port>
                </replica>
                <replica>
                    <host>9.30.199.125</host>
                    <port>9000</port>
                </replica>
            </shard>
            <shard>   <!-- add extra shard is needed>
            ...
            </shard> 
        </groupby_test>        
    ```
- Add zookeeper config:
    ```
        <zookeeper>
            <node index="1">
                <host>9.30.188.170</host>
                <port>2181</port>
            </node>
            <node index="3">
                <host>9.30.230.135</host>
                <port>2181</port>
            </node>
            <node index="3">
                <host>9.30.199.125</host>
                <port>2181</port>
            </node>
        </zookeeper>
    ```
- Change macro for 9.30.188.170  
    ```
        <macros>
            <shard>1</shard>
            <replica>9.30.188.170</replica>
        </macros>
    ```
- Change macro for 9.30.199.125 
    ```
        <macros>
            <shard>1</shard>
            <replica>9.30.199.125</replica>
        </macros>
    ```
- Start server on both machine

    ```
    sudo service clickhouse-server start

    ```
- Run client on one machine and check cluster:
    ```
    clickhouse-client
    
    SELECT *
    FROM system.clusters

    Query id: c015f717-c871-4061-b9b3-dd0d00bd51e0

    ┌─cluster────────┬─shard_num─┬─shard_weight─┬─replica_num─┬─host_name────┬─host_address─┬─port─┬─is_local─┬─user────┬─default_database─┬─errors_count─┬─slowdowns_count─┬─estimated_recovery_time─┐
    │ groupby_test   │         1 │            1 │           1 │ 9.30.188.170 │ 9.30.188.170 │ 9000 │        1 │ default │                  │            0 │               0 │                       0 │
    │ groupby_test   │         1 │            1 │           2 │ 9.30.199.125 │ 9.30.199.125 │ 9000 │        0 │ default │                  │            0 │               0 │                       0 │
    | ...            |           |              |             |              |              |      |          |         |                  |              |                 |                         |
    └────────────────┴───────────┴──────────────┴─────────────┴──────────────┴──────────────┴──────┴──────────┴─────────┴──────────────────┴──────────────┴─────────────────┴─────────────────────────┘

    ```


## 4. Try to reproduce issue (Build DB on cluster)  
run on one of the machines.  
- Create database
    ```sql
    CREATE DATABASE IF NOT EXISTS shared ON CLUSTER 'groupby_test';
    ```
- Create tables: 
    ```sql
    CREATE TABLE IF NOT EXISTS shared.website_monitoring_beacons ON CLUSTER groupby_test (
        `client_id` String,
        `sample_multiplicity` UInt64 DEFAULT 1,
        `website_id` String,
        `page` String,
        `phase` String,
        `timestamp` UInt64,
        `timestampDate` Date MATERIALIZED toDate(timestamp / 1000),
        `duration` UInt64,
        `batch_size` UInt64,
        `accurate_timings_available` UInt8,
        `deprecations` Array(String),
        `page_load_id` String,
        `beacon_id` String,
        `backend_trace_id` String,
        `type` String,
        `custom_event_name` String,
        `meta.key` Array(String),
        `meta.value` Array(String),
        `location_url` String,
        `location_origin` String,
        `location_path` String,
        `error_count` UInt64,
        `erroneous` UInt8 MATERIALIZED error_count > 0,
        `error_message` String,
        `error_id` String,
        `stack_trace` String,
        `component_stack` String,
        `user_ip` String,
        `user_id` String,
        `user_name` String,
        `user_email` String,
        `user_languages` Array(String),
        `device_type` String,
        `browser_name` String,
        `browser_version` String,
        `os_name` String,
        `os_version` String,
        `window_hidden` UInt8,
        `window_width` UInt64,
        `window_height` UInt64,
        `latitude` String,
        `longitude` String,
        `city` String,
        `country` String,
        `continent` String,
        `http_call_url` String,
        `http_call_origin` String,
        `http_call_path` String,
        `http_call_method` String,
        `http_call_status` String,
        `http_call_correlation_attempted` UInt8,
        `http_call_asynchronous` UInt8,
        `initiator` String,
        `resource_type` String,
        `cache_interaction` String,
        `encoded_body_size` UInt64,
        `decoded_body_size` UInt64,
        `transfer_size` UInt64,
        `unload_time` UInt64,
        `redirect_time` UInt64,
        `app_cache_time` UInt64,
        `dns_time` UInt64,
        `tcp_time` UInt64,
        `ssl_time` UInt64,
        `request_time` UInt64,
        `response_time` UInt64,
        `processing_time` UInt64,
        `on_load_time` UInt64,
        `backend_time` UInt64,
        `frontend_time` UInt64,
        `dom_time` UInt64,
        `children_time` UInt64,
        `first_paint_time` UInt64,
        `first_contentful_paint_time` UInt64,
        `error_type` String,
        `subdivision` String,
        `t` UInt64 MATERIALIZED timestamp,
        `accuracy_radius` UInt64,
        `subdivision_code` String,
        `country_code` String,
        `continent_code` String,
        `ingestion_time` UInt64,
        `connection_type` String,
        `stack_trace_parsing_status` UInt64,
        `parsed_stack_trace.file` Array(String),
        `parsed_stack_trace.name` Array(String),
        `parsed_stack_trace.line` Array(UInt64),
        `parsed_stack_trace.column` Array(UInt64),
        `parsed_stack_trace.translation_status` Array(UInt64),
        `stack_trace_readability` UInt64,
        `clock_skew` UInt64,
        `csp_blocked_uri` String,
        `csp_effective_directive` String,
        `csp_original_policy` String,
        `csp_disposition` String,
        `csp_sample` String,
        `csp_source_file` String,
        `csp_line_number` UInt64,
        `csp_column_number` UInt64,
        `parsed_stack_trace.translation_explanation` Array(String),
        `session_id` String,
        `user_id_or_session_id` String MATERIALIZED if(empty(user_id) = 1,
    session_id,
    user_id),
        `largest_contentful_paint_time` UInt64,
        `first_input_delay_time` UInt64,
        `cumulative_layout_shift` UInt64,
        `graphql_operation_name` LowCardinality(String),
        `graphql_operation_type` LowCardinality(String),
        `snippet_version` LowCardinality(String),
        `header.key` Array(LowCardinality(String)),
        `header.value` Array(LowCardinality(String))

    ) ENGINE = ReplicatedMergeTree('/clickhouse/tables/{shard}/shared/website_monitoring_beacons', '{replica}')
    PARTITION BY toRelativeDayNum(timestampDate)
    ORDER BY (client_id, timestamp)
    SETTINGS index_granularity=8192;
    ```

    ```sql
    CREATE TABLE IF NOT EXISTS shared.website_monitoring_beacons_aggregated_1m ON CLUSTER groupby_test (
    client_id                                           LowCardinality(String),
    t                                                   UInt64,
    type                                                LowCardinality(String),
    browser_name                                        LowCardinality(String),
    cache_interaction                                   LowCardinality(String),
    custom_event_name                                   LowCardinality(String),
    connection_type                                     LowCardinality(String),
    error_id                                            LowCardinality(String),
    error_type                                          LowCardinality(String),
    country                                             LowCardinality(String),
    country_code                                        LowCardinality(String),
    continent                                           LowCardinality(String),
    continent_code                                      LowCardinality(String),
    subdivision                                         LowCardinality(String),
    graphql_operation_name                              LowCardinality(String),
    http_call_origin                                    LowCardinality(String),
    os_name                                             LowCardinality(String),
    page                                                LowCardinality(String),
    resource_type                                       LowCardinality(String),
    website_id                                          LowCardinality(String),
    has_user_id_or_session_id                           UInt8,
    distinct_count_unique_users_or_sessions_state       AggregateFunction(uniq, String),
    max_app_cache_time_state                            AggregateFunction(max, UInt64),
    max_beacon_duration_state                           AggregateFunction(max, UInt64),
    max_children_time_state                             AggregateFunction(max, UInt64),
    max_cumulative_layout_shift_state                   AggregateFunction(max, UInt64),
    max_decoded_body_size_state                         AggregateFunction(max, UInt64),
    max_dns_time_state                                  AggregateFunction(max, UInt64),
    max_dom_time_state                                  AggregateFunction(max, UInt64),
    max_encoded_body_size_state                         AggregateFunction(max, UInt64),
    max_first_contentful_paint_time_state               AggregateFunction(max, UInt64),
    max_first_input_delay_state                         AggregateFunction(max, UInt64),
    max_first_paint_time_state                          AggregateFunction(max, UInt64),
    max_largest_contentful_paint_time_state             AggregateFunction(max, UInt64),
    max_redirect_time_state                             AggregateFunction(max, UInt64),
    max_request_time_state                              AggregateFunction(max, UInt64),
    max_response_time_state                             AggregateFunction(max, UInt64),
    max_ssl_time_state                                  AggregateFunction(max, UInt64),
    max_tcp_time_state                                  AggregateFunction(max, UInt64),
    max_transfer_size_state                             AggregateFunction(max, UInt64),
    max_ttfb_state                                      AggregateFunction(max, UInt64),
    max_unload_time_state                               AggregateFunction(max, UInt64),
    count_app_cache_time_state                          AggregateFunction(sum, UInt64),
    sum_app_cache_time_state                            AggregateFunction(sum, UInt64),
    count_beacon_duration_state                         AggregateFunction(sum, UInt64),
    sum_beacon_duration_state                           AggregateFunction(sum, UInt64),
    count_children_time_state                           AggregateFunction(sum, UInt64),
    sum_children_time_state                             AggregateFunction(sum, UInt64),
    count_cumulative_layout_shift_state                 AggregateFunction(sum, UInt64),
    sum_cumulative_layout_shift_state                   AggregateFunction(sum, UInt64),
    count_decoded_body_size_state                       AggregateFunction(sum, UInt64),
    sum_decoded_body_size_state                         AggregateFunction(sum, UInt64),
    count_dns_time_state                                AggregateFunction(sum, UInt64),
    sum_dns_time_state                                  AggregateFunction(sum, UInt64),
    count_dom_time_state                                AggregateFunction(sum, UInt64),
    sum_dom_time_state                                  AggregateFunction(sum, UInt64),
    count_encoded_body_size_state                       AggregateFunction(sum, UInt64),
    sum_encoded_body_size_state                         AggregateFunction(sum, UInt64),
    count_first_contentful_paint_time_state             AggregateFunction(sum, UInt64),
    sum_first_contentful_paint_time_state               AggregateFunction(sum, UInt64),
    count_first_input_delay_state                       AggregateFunction(sum, UInt64),
    sum_first_input_delay_state                         AggregateFunction(sum, UInt64),
    count_first_paint_time_state                        AggregateFunction(sum, UInt64),
    sum_first_paint_time_state                          AggregateFunction(sum, UInt64),
    count_largest_contentful_paint_time_state           AggregateFunction(sum, UInt64),
    sum_largest_contentful_paint_time_state             AggregateFunction(sum, UInt64),
    count_redirect_time_state                           AggregateFunction(sum, UInt64),
    sum_redirect_time_state                             AggregateFunction(sum, UInt64),
    count_request_time_state                            AggregateFunction(sum, UInt64),
    sum_request_time_state                              AggregateFunction(sum, UInt64),
    count_response_time_state                           AggregateFunction(sum, UInt64),
    sum_response_time_state                             AggregateFunction(sum, UInt64),
    count_ssl_time_state                                AggregateFunction(sum, UInt64),
    sum_ssl_time_state                                  AggregateFunction(sum, UInt64),
    count_tcp_time_state                                AggregateFunction(sum, UInt64),
    sum_tcp_time_state                                  AggregateFunction(sum, UInt64),
    count_transfer_size_state                           AggregateFunction(sum, UInt64),
    sum_transfer_size_state                             AggregateFunction(sum, UInt64),
    count_ttfb_state                                    AggregateFunction(sum, UInt64),
    sum_ttfb_state                                      AggregateFunction(sum, UInt64),
    count_unload_time_state                             AggregateFunction(sum, UInt64),
    sum_unload_time_state                               AggregateFunction(sum, UInt64),
    min_app_cache_time_state                            AggregateFunction(min, UInt64),
    min_children_time_state                             AggregateFunction(min, UInt64),
    min_cumulative_layout_shift_state                   AggregateFunction(min, UInt64),
    min_decoded_body_size_state                         AggregateFunction(min, UInt64),
    min_dns_time_state                                  AggregateFunction(min, UInt64),
    min_dom_time_state                                  AggregateFunction(min, UInt64),
    min_encoded_body_size_state                         AggregateFunction(min, UInt64),
    min_first_contentful_paint_time_state               AggregateFunction(min, UInt64),
    min_first_input_delay_state                         AggregateFunction(min, UInt64),
    min_first_paint_time_state                          AggregateFunction(min, UInt64),
    min_largest_contentful_paint_time_state             AggregateFunction(min, UInt64),
    min_redirect_time_state                             AggregateFunction(min, UInt64),
    min_request_time_state                              AggregateFunction(min, UInt64),
    min_response_time_state                             AggregateFunction(min, UInt64),
    min_ssl_time_state                                  AggregateFunction(min, UInt64),
    min_tcp_time_state                                  AggregateFunction(min, UInt64),
    min_transfer_size_state                             AggregateFunction(min, UInt64),
    min_ttfb_state                                      AggregateFunction(min, UInt64),
    min_unload_time_state                               AggregateFunction(min, UInt64),
    quantiles_app_cache_time_large_state                AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_app_cache_time_state                      AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_app_cache_time_exact_state                AggregateFunction(quantilesExactWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_beacon_duration_large_state               AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_beacon_duration_state                     AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_beacon_duration_exact_state               AggregateFunction(quantilesExactWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_children_time_large_state                 AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_children_time_state                       AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_children_time_exact_state                 AggregateFunction(quantilesExactWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_cumulative_layout_shift_large_state       AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_cumulative_layout_shift_state             AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_cumulative_layout_shift_exact_state       AggregateFunction(quantilesExactWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_decoded_body_size_large_state             AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_decoded_body_size_state                   AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_decoded_body_size_exact_state             AggregateFunction(quantilesExactWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_dns_time_large_state                      AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_dns_time_state                            AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_dns_time_exact_state                      AggregateFunction(quantilesExactWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_dom_time_large_state                      AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_dom_time_state                            AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_dom_time_exact_state                      AggregateFunction(quantilesExactWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_encoded_body_size_large_state             AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_encoded_body_size_state                   AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_encoded_body_size_exact_state             AggregateFunction(quantilesExactWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_first_contentful_paint_time_large_state   AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_first_contentful_paint_time_state         AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_first_contentful_paint_time_exact_state   AggregateFunction(quantilesExactWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_first_input_delay_large_state             AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_first_input_delay_state                   AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_first_input_delay_exact_state             AggregateFunction(quantilesExactWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_first_paint_time_large_state              AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_first_paint_time_state                    AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_first_paint_time_exact_state              AggregateFunction(quantilesExactWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_largest_contentful_paint_time_large_state AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_largest_contentful_paint_time_state       AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_largest_contentful_paint_time_exact_state AggregateFunction(quantilesExactWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_redirect_time_large_state                 AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_redirect_time_state                       AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_redirect_time_exact_state                 AggregateFunction(quantilesExactWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_request_time_large_state                  AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_request_time_state                        AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_request_time_exact_state                  AggregateFunction(quantilesExactWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_response_time_large_state                 AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_response_time_state                       AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_response_time_exact_state                 AggregateFunction(quantilesExactWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_ssl_time_large_state                      AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_ssl_time_state                            AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_ssl_time_exact_state                      AggregateFunction(quantilesExactWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_tcp_time_large_state                      AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_tcp_time_state                            AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_tcp_time_exact_state                      AggregateFunction(quantilesExactWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_transfer_size_large_state                 AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_transfer_size_state                       AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_transfer_size_exact_state                 AggregateFunction(quantilesExactWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_ttfb_large_state                          AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_ttfb_state                                AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_ttfb_exact_state                          AggregateFunction(quantilesExactWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_unload_time_large_state                   AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_unload_time_state                         AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    quantiles_unload_time_exact_state                   AggregateFunction(quantilesExactWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
    sum_beacon_count_state                              AggregateFunction(sum, UInt64),
    sum_beacon_error_count_state                        AggregateFunction(sum, UInt64),
    sum_http1xx_state                                   AggregateFunction(sum, UInt64),
    sum_http2xx_state                                   AggregateFunction(sum, UInt64),
    sum_http3xx_state                                   AggregateFunction(sum, UInt64),
    sum_http4xx_state                                   AggregateFunction(sum, UInt64),
    sum_http5xx_state                                   AggregateFunction(sum, UInt64),
    sum_http_delete_state                               AggregateFunction(sum, UInt64),
    sum_http_get_state                                  AggregateFunction(sum, UInt64),
    sum_http_post_state                                 AggregateFunction(sum, UInt64),
    sum_http_put_state                                  AggregateFunction(sum, UInt64),

    INDEX minmax_t t TYPE minmax GRANULARITY 1
    )
    ENGINE = ReplicatedAggregatingMergeTree('/clickhouse/tables/{shard}/shared/website_monitoring_beacons_aggregated_1m','{replica}')
    PRIMARY KEY (client_id, type, t)
    PARTITION BY toRelativeDayNum(toDate(t / 1000))
    ORDER BY (
    client_id,
    type,
    t,
    website_id,
    browser_name,
    cache_interaction,
    custom_event_name,
    connection_type,
    error_id,
    error_type,
    country,
    country_code,
    continent,
    continent_code,
    subdivision,
    graphql_operation_name,
    http_call_origin,
    os_name,
    page,
    resource_type,
    has_user_id_or_session_id
    )
    SETTINGS index_granularity = 8192
    ```

    ```sql
    ALTER TABLE shared.website_monitoring_beacons_aggregated_1m ON CLUSTER groupby_test
    ADD COLUMN IF NOT EXISTS min_beacon_duration_state AggregateFunction(min, UInt64);

    ALTER TABLE shared.website_monitoring_beacons_aggregated_1m ON CLUSTER groupby_test
        ADD COLUMN IF NOT EXISTS `min_ingestion_time_state` SimpleAggregateFunction(min, UInt64),
        ADD COLUMN IF NOT EXISTS `max_ingestion_time_state` SimpleAggregateFunction(max, UInt64),
        ADD COLUMN IF NOT EXISTS `min_timestamp_state`      SimpleAggregateFunction(min, UInt64);

    ALTER TABLE shared.website_monitoring_beacons_aggregated_1m ON CLUSTER groupby_test
    ADD INDEX IF NOT EXISTS set_website_id website_id TYPE set(50) GRANULARITY 1;
    ```
- CREATE MATERIALIZED VIEW    
    ```sql
    CREATE MATERIALIZED VIEW IF NOT EXISTS shared.website_monitoring_beacons_aggregated_1m_mv ON CLUSTER groupby_test 
        TO shared.website_monitoring_beacons_aggregated_1m
    AS
    WITH
        9223372036854775807 AS maxInt64,
        toUInt64(ceil(app_cache_time / batch_size))                     AS single_app_cache_time,
        toUInt64(ceil(children_time / batch_size))                      AS single_children_time,
        toUInt64(ceil(cumulative_layout_shift / batch_size))            AS single_cumulative_layout_shift,
        toUInt64(ceil(decoded_body_size / batch_size))                  AS single_decoded_body_size,
        toUInt64(ceil(dns_time / batch_size))                           AS single_dns_time,
        toUInt64(ceil(dom_time / batch_size))                           AS single_dom_time,
        toUInt64(ceil(encoded_body_size / batch_size))                  AS single_encoded_body_size,
        toUInt64(ceil(first_contentful_paint_time / batch_size))        AS single_first_contentful_paint_time,
        toUInt64(ceil(first_input_delay_time / batch_size))             AS single_first_input_delay_time,
        toUInt64(ceil(first_paint_time / batch_size))                   AS single_first_paint_time,
        toUInt64(ceil(largest_contentful_paint_time / batch_size))      AS single_largest_contentful_paint_time,
        toUInt64(ceil(duration / batch_size))                           AS single_duration,
        toUInt64(ceil(redirect_time / batch_size))                      AS single_redirect_time,
        toUInt64(ceil(request_time / batch_size))                       AS single_request_time,
        toUInt64(ceil(response_time / batch_size))                      AS single_response_time,
        toUInt64(ceil(ssl_time / batch_size))                           AS single_ssl_time,
        toUInt64(ceil(tcp_time / batch_size))                           AS single_tcp_time,
        toUInt64(ceil(transfer_size / batch_size))                      AS single_transfer_size,
        toUInt64(ceil(backend_time / batch_size))                       AS single_backend_time,
        toUInt64(ceil(unload_time / batch_size))                        AS single_unload_time
    SELECT
        client_id,
        toUInt64(floor(t / 60000) * 60000) AS t,
        type,
        browser_name,
        cache_interaction,
        custom_event_name,
        connection_type,
        error_id,
        error_type,
        country,
        country_code,
        continent,
        continent_code,
        subdivision,
        graphql_operation_name,
        http_call_origin,
        os_name,
        page,
        resource_type,
        website_id,
        notEmpty(user_id_or_session_id)                                                                    AS `has_user_id_or_session_id`,
        uniqStateIf(user_id_or_session_id, notEmpty(user_id_or_session_id) = 1)                            AS `distinct_count_unique_users_or_sessions_state`,
        maxStateIf(single_app_cache_time, app_cache_time != maxInt64)                                      AS `max_app_cache_time_state`,
        maxStateIf(single_children_time, children_time != maxInt64)                                        AS `max_children_time_state`,
        maxStateIf(single_cumulative_layout_shift, cumulative_layout_shift != maxInt64)                    AS `max_cumulative_layout_shift_state`,
        maxStateIf(single_decoded_body_size, decoded_body_size != maxInt64)                                AS `max_decoded_body_size_state`,
        maxStateIf(single_dns_time, dns_time != maxInt64)                                                  AS `max_dns_time_state`,
        maxStateIf(single_dom_time, dom_time != maxInt64)                                                  AS `max_dom_time_state`,
        maxStateIf(single_encoded_body_size, encoded_body_size != maxInt64)                                AS `max_encoded_body_size_state`,
        maxStateIf(single_first_contentful_paint_time, first_contentful_paint_time != maxInt64)            AS `max_first_contentful_paint_time_state`,
        maxStateIf(single_first_input_delay_time, first_input_delay_time != maxInt64)                      AS `max_first_input_delay_state`,
        maxStateIf(single_first_paint_time, first_paint_time != maxInt64)                                  AS `max_first_paint_time_state`,
        maxStateIf(single_largest_contentful_paint_time, largest_contentful_paint_time != maxInt64)        AS `max_largest_contentful_paint_time_state`,
        maxStateIf(single_duration, duration != maxInt64)                                                  AS `max_beacon_duration_state`,
        maxStateIf(single_redirect_time, redirect_time != maxInt64)                                        AS `max_redirect_time_state`,
        maxStateIf(single_request_time, request_time != maxInt64)                                          AS `max_request_time_state`,
        maxStateIf(single_response_time, response_time != maxInt64)                                        AS `max_response_time_state`,
        maxStateIf(single_ssl_time, ssl_time != maxInt64)                                                  AS `max_ssl_time_state`,
        maxStateIf(single_tcp_time, tcp_time != maxInt64)                                                  AS `max_tcp_time_state`,
        maxStateIf(single_transfer_size, transfer_size != maxInt64)                                        AS `max_transfer_size_state`,
        maxStateIf(single_backend_time, backend_time != maxInt64)                                          AS `max_ttfb_state`,
        maxStateIf(single_unload_time, unload_time != maxInt64)                                            AS `max_unload_time_state`,
        sumStateIf(batch_size, app_cache_time != maxInt64)                                                 AS `count_app_cache_time_state`,
        sumStateIf(app_cache_time, app_cache_time != maxInt64)                                             AS `sum_app_cache_time_state`,
        sumStateIf(batch_size, duration != maxInt64)                                                       AS `count_beacon_duration_state`,
        sumStateIf(duration, duration != maxInt64)                                                         AS `sum_beacon_duration_state`,
        sumStateIf(batch_size, children_time != maxInt64)                                                  AS `count_children_time_state`,
        sumStateIf(children_time, children_time != maxInt64)                                               AS `sum_children_time_state`,
        sumStateIf(batch_size, cumulative_layout_shift != maxInt64)                                        AS `count_cumulative_layout_shift_state`,
        sumStateIf(cumulative_layout_shift, cumulative_layout_shift != maxInt64)                           AS `sum_cumulative_layout_shift_state`,
        sumStateIf(batch_size, decoded_body_size != maxInt64)                                              AS `count_decoded_body_size_state`,
        sumStateIf(decoded_body_size, decoded_body_size != maxInt64)                                       AS `sum_decoded_body_size_state`,
        sumStateIf(batch_size, dns_time != maxInt64)                                                       AS `count_dns_time_state`,
        sumStateIf(dns_time, dns_time != maxInt64)                                                         AS `sum_dns_time_state`,
        sumStateIf(batch_size, dom_time != maxInt64)                                                       AS `count_dom_time_state`,
        sumStateIf(dom_time, dom_time != maxInt64)                                                         AS `sum_dom_time_state`,
        sumStateIf(batch_size, encoded_body_size != maxInt64)                                              AS `count_encoded_body_size_state`,
        sumStateIf(encoded_body_size, encoded_body_size != maxInt64)                                       AS `sum_encoded_body_size_state`,
        sumStateIf(batch_size, first_contentful_paint_time != maxInt64)                                    AS `count_first_contentful_paint_time_state`,
        sumStateIf(first_contentful_paint_time, first_contentful_paint_time != maxInt64)                   AS `sum_first_contentful_paint_time_state`,
        sumStateIf(batch_size, first_input_delay_time != maxInt64)                                         AS `count_first_input_delay_state`,
        sumStateIf(first_input_delay_time, first_input_delay_time != maxInt64)                             AS `sum_first_input_delay_state`,
        sumStateIf(batch_size, first_paint_time != maxInt64)                                               AS `count_first_paint_time_state`,
        sumStateIf(first_paint_time, first_paint_time != maxInt64)                                         AS `sum_first_paint_time_state`,
        sumStateIf(batch_size, largest_contentful_paint_time != maxInt64)                                  AS `count_largest_contentful_paint_time_state`,
        sumStateIf(largest_contentful_paint_time, largest_contentful_paint_time != maxInt64)               AS `sum_largest_contentful_paint_time_state`,
        sumStateIf(batch_size, redirect_time != maxInt64)                                                  AS `count_redirect_time_state`,
        sumStateIf(redirect_time, redirect_time != maxInt64)                                               AS `sum_redirect_time_state`,
        sumStateIf(batch_size, request_time != maxInt64)                                                   AS `count_request_time_state`,
        sumStateIf(request_time, request_time != maxInt64)                                                 AS `sum_request_time_state`,
        sumStateIf(batch_size, response_time != maxInt64)                                                  AS `count_response_time_state`,
        sumStateIf(response_time, response_time != maxInt64)                                               AS `sum_response_time_state`,
        sumStateIf(batch_size, ssl_time != maxInt64)                                                       AS `count_ssl_time_state`,
        sumStateIf(ssl_time, ssl_time != maxInt64)                                                         AS `sum_ssl_time_state`,
        sumStateIf(batch_size, tcp_time != maxInt64)                                                       AS `count_tcp_time_state`,
        sumStateIf(tcp_time, tcp_time != maxInt64)                                                         AS `sum_tcp_time_state`,
        sumStateIf(batch_size, transfer_size != maxInt64)                                                  AS `count_transfer_size_state`,
        sumStateIf(transfer_size, transfer_size != maxInt64)                                               AS `sum_transfer_size_state`,
        sumStateIf(batch_size, backend_time != maxInt64)                                                   AS `count_ttfb_state`,
        sumStateIf(backend_time, backend_time != maxInt64)                                                 AS `sum_ttfb_state`,
        sumStateIf(batch_size, unload_time != maxInt64)                                                    AS `count_unload_time_state`,
        sumStateIf(unload_time, unload_time != maxInt64)                                                   AS `sum_unload_time_state`,
        minStateIf(single_app_cache_time, app_cache_time != maxInt64)                                      AS `min_app_cache_time_state`,
        minStateIf(single_children_time, children_time != maxInt64)                                        AS `min_children_time_state`,
        minStateIf(single_cumulative_layout_shift, cumulative_layout_shift != maxInt64)                    AS `min_cumulative_layout_shift_state`,
        minStateIf(single_decoded_body_size, decoded_body_size != maxInt64)                                AS `min_decoded_body_size_state`,
        minStateIf(single_dns_time, dns_time != maxInt64)                                                  AS `min_dns_time_state`,
        minStateIf(single_dom_time, dom_time != maxInt64)                                                  AS `min_dom_time_state`,
        minStateIf(single_encoded_body_size, encoded_body_size != maxInt64)                                AS `min_encoded_body_size_state`,
        minStateIf(single_first_contentful_paint_time, first_contentful_paint_time != maxInt64)            AS `min_first_contentful_paint_time_state`,
        minStateIf(single_first_input_delay_time, first_input_delay_time != maxInt64)                      AS `min_first_input_delay_state`,
        minStateIf(single_first_paint_time, first_paint_time != maxInt64)                                  AS `min_first_paint_time_state`,
        minStateIf(single_largest_contentful_paint_time, largest_contentful_paint_time != maxInt64)        AS `min_largest_contentful_paint_time_state`,
        minStateIf(single_duration, duration != maxInt64)                                                  AS `min_beacon_duration_state`,
        minStateIf(single_redirect_time, redirect_time != maxInt64)                                        AS `min_redirect_time_state`,
        minStateIf(single_request_time, request_time != maxInt64)                                          AS `min_request_time_state`,
        minStateIf(single_response_time, response_time != maxInt64)                                        AS `min_response_time_state`,
        minStateIf(single_ssl_time, ssl_time != maxInt64)                                                  AS `min_ssl_time_state`,
        minStateIf(single_tcp_time, tcp_time != maxInt64)                                                  AS `min_tcp_time_state`,
        minStateIf(single_transfer_size, transfer_size != maxInt64)                                        AS `min_transfer_size_state`,
        minStateIf(single_backend_time, backend_time != maxInt64)                                          AS `min_ttfb_state`,
        minStateIf(single_unload_time, unload_time != maxInt64)                                            AS `min_unload_time_state`,
        minSimpleState(ingestion_time)                                                                     AS `min_ingestion_time_state`,
        maxSimpleState(ingestion_time)                                                                     AS `max_ingestion_time_state`,
        minSimpleState(timestamp)                                                                          AS `min_timestamp_state`,
        quantilesTimingWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                toUInt64(single_app_cache_time / 100),
                                batch_size,
                                app_cache_time != maxInt64)                                             AS `quantiles_app_cache_time_large_state`,
        quantilesTimingWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                single_app_cache_time,
                                batch_size,
                                app_cache_time != maxInt64)                                             AS `quantiles_app_cache_time_state`,
        quantilesExactWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                single_app_cache_time,
                                batch_size,
                                app_cache_time != maxInt64)                                             AS `quantiles_app_cache_time_exact_state`,
        quantilesTimingWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                toUInt64(single_duration / 100),
                                batch_size,
                                duration != maxInt64)                                                   AS `quantiles_beacon_duration_large_state`,
        quantilesTimingWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                single_duration,
                                batch_size,
                                duration != maxInt64)                                                   AS `quantiles_beacon_duration_state`,
        quantilesExactWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                single_duration,
                                batch_size,
                                duration != maxInt64)                                                   AS `quantiles_beacon_duration_exact_state`,
        quantilesTimingWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                toUInt64(single_children_time / 100),
                                batch_size,
                                children_time != maxInt64)                                              AS `quantiles_children_time_large_state`,
        quantilesTimingWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                single_children_time,
                                batch_size,
                                children_time != maxInt64)                                              AS `quantiles_children_time_state`,
        quantilesExactWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                single_children_time,
                                batch_size,
                                children_time != maxInt64)                                              AS `quantiles_children_time_exact_state`,
        quantilesTimingWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                toUInt64(single_cumulative_layout_shift / 100),
                                batch_size,
                                cumulative_layout_shift != maxInt64)                                    AS `quantiles_cumulative_layout_shift_large_state`,
        quantilesTimingWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                single_cumulative_layout_shift,
                                batch_size,
                                cumulative_layout_shift != maxInt64)                                    AS `quantiles_cumulative_layout_shift_state`,
        quantilesExactWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                single_cumulative_layout_shift,
                                batch_size,
                                cumulative_layout_shift != maxInt64)                                    AS `quantiles_cumulative_layout_shift_exact_state`,
        quantilesTimingWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                toUInt64(single_decoded_body_size / 100),
                                batch_size,
                                decoded_body_size != maxInt64)                                          AS `quantiles_decoded_body_size_large_state`,
        quantilesTimingWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                single_decoded_body_size,
                                batch_size,
                                decoded_body_size != maxInt64)                                          AS `quantiles_decoded_body_size_state`,
        quantilesExactWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                single_decoded_body_size,
                                batch_size,
                                decoded_body_size != maxInt64)                                          AS `quantiles_decoded_body_size_exact_state`,
        quantilesTimingWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                toUInt64(single_dns_time / 100),
                                batch_size,
                                dns_time != maxInt64)                                                   AS `quantiles_dns_time_large_state`,
        quantilesTimingWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                single_dns_time,
                                batch_size,
                                dns_time != maxInt64)                                                   AS `quantiles_dns_time_state`,
        quantilesExactWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                single_dns_time,
                                batch_size,
                                dns_time != maxInt64)                                                   AS `quantiles_dns_time_exact_state`,
        quantilesTimingWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                toUInt64(single_dom_time / 100),
                                batch_size,
                                dom_time != maxInt64)                                                   AS `quantiles_dom_time_large_state`,
        quantilesTimingWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                single_dom_time,
                                batch_size,
                                dom_time != maxInt64)                                                   AS `quantiles_dom_time_state`,
        quantilesExactWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                single_dom_time,
                                batch_size,
                                dom_time != maxInt64)                                                   AS `quantiles_dom_time_exact_state`,
        quantilesTimingWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                toUInt64(single_encoded_body_size / 100),
                                batch_size,
                                encoded_body_size != maxInt64)                                          AS `quantiles_encoded_body_size_large_state`,
        quantilesTimingWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                single_encoded_body_size,
                                batch_size,
                                encoded_body_size != maxInt64)                                          AS `quantiles_encoded_body_size_state`,
        quantilesExactWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                single_encoded_body_size,
                                batch_size,
                                encoded_body_size != maxInt64)                                          AS `quantiles_encoded_body_size_exact_state`,
        quantilesTimingWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                toUInt64(single_first_contentful_paint_time / 100),
                                batch_size,
                                first_contentful_paint_time != maxInt64)                                AS `quantiles_first_contentful_paint_time_large_state`,
        quantilesTimingWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                single_first_contentful_paint_time,
                                batch_size,
                                first_contentful_paint_time != maxInt64)                                AS `quantiles_first_contentful_paint_time_state`,
        quantilesExactWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                single_first_contentful_paint_time,
                                batch_size,
                                first_contentful_paint_time != maxInt64)                                AS `quantiles_first_contentful_paint_time_exact_state`,
        quantilesTimingWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                toUInt64(single_first_input_delay_time / 100),
                                batch_size,
                                first_input_delay_time != maxInt64)                                     AS `quantiles_first_input_delay_large_state`,
        quantilesTimingWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                single_first_input_delay_time,
                                batch_size,
                                first_input_delay_time != maxInt64)                                     AS `quantiles_first_input_delay_state`,
        quantilesExactWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                single_first_input_delay_time,
                                batch_size,
                                first_input_delay_time != maxInt64)                                     AS `quantiles_first_input_delay_exact_state`,
        quantilesTimingWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                toUInt64(single_first_paint_time / 100),
                                batch_size,
                                first_paint_time != maxInt64)                                           AS `quantiles_first_paint_time_large_state`,
        quantilesTimingWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                single_first_paint_time,
                                batch_size,
                                first_paint_time != maxInt64)                                           AS `quantiles_first_paint_time_state`,
        quantilesExactWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                single_first_paint_time,
                                batch_size,
                                first_paint_time != maxInt64)                                           AS `quantiles_first_paint_time_exact_state`,
        quantilesTimingWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                toUInt64(single_largest_contentful_paint_time / 100),
                                batch_size,
                                largest_contentful_paint_time != maxInt64)                              AS `quantiles_largest_contentful_paint_time_large_state`,
        quantilesTimingWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                single_largest_contentful_paint_time,
                                batch_size,
                                largest_contentful_paint_time != maxInt64)                              AS `quantiles_largest_contentful_paint_time_state`,
        quantilesExactWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                single_largest_contentful_paint_time,
                                batch_size,
                                largest_contentful_paint_time != maxInt64)                              AS `quantiles_largest_contentful_paint_time_exact_state`,
        quantilesTimingWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                toUInt64(single_redirect_time / 100),
                                batch_size,
                                redirect_time != maxInt64)                                              AS `quantiles_redirect_time_large_state`,
        quantilesTimingWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                single_redirect_time,
                                batch_size,
                                redirect_time != maxInt64)                                              AS `quantiles_redirect_time_state`,
        quantilesExactWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                single_redirect_time,
                                batch_size,
                                redirect_time != maxInt64)                                              AS `quantiles_redirect_time_exact_state`,
        quantilesTimingWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                toUInt64(single_request_time / 100),
                                batch_size,
                                request_time != maxInt64)                                               AS `quantiles_request_time_large_state`,
        quantilesTimingWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                single_request_time,
                                batch_size,
                                request_time != maxInt64)                                               AS `quantiles_request_time_state`,
        quantilesExactWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                single_request_time,
                                batch_size,
                                request_time != maxInt64)                                               AS `quantiles_request_time_exact_state`,
        quantilesTimingWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                toUInt64((single_response_time / 100)),
                                batch_size,
                                response_time != maxInt64)                                              AS `quantiles_response_time_large_state`,
        quantilesTimingWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                single_response_time,
                                batch_size,
                                response_time != maxInt64)                                              AS `quantiles_response_time_state`,
        quantilesExactWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                single_response_time,
                                batch_size,
                                response_time != maxInt64)                                              AS `quantiles_response_time_exact_state`,
        quantilesTimingWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                toUInt64(single_ssl_time / 100),
                                batch_size,
                                ssl_time != maxInt64)                                                   AS `quantiles_ssl_time_large_state`,
        quantilesTimingWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                single_ssl_time,
                                batch_size,
                                ssl_time != maxInt64)                                                   AS `quantiles_ssl_time_state`,
        quantilesExactWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                single_ssl_time,
                                batch_size,
                                ssl_time != maxInt64)                                                   AS `quantiles_ssl_time_exact_state`,
        quantilesTimingWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                toUInt64(single_tcp_time / 100),
                                batch_size,
                                tcp_time != maxInt64)                                                   AS `quantiles_tcp_time_large_state`,
        quantilesTimingWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                single_tcp_time,
                                batch_size,
                                tcp_time != maxInt64)                                                   AS `quantiles_tcp_time_state`,
        quantilesExactWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                single_tcp_time,
                                batch_size,
                                tcp_time != maxInt64)                                                   AS `quantiles_tcp_time_exact_state`,
        quantilesTimingWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                toUInt64(single_transfer_size / 100),
                                batch_size,
                                transfer_size != maxInt64)                                              AS `quantiles_transfer_size_large_state`,
        quantilesTimingWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                single_transfer_size,
                                batch_size,
                                transfer_size != maxInt64)                                              AS `quantiles_transfer_size_state`,
        quantilesExactWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                single_transfer_size,
                                batch_size,
                                transfer_size != maxInt64)                                              AS `quantiles_transfer_size_exact_state`,
        quantilesTimingWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                toUInt64(single_backend_time / 100),
                                batch_size,
                                backend_time != maxInt64)                                               AS `quantiles_ttfb_large_state`,
        quantilesTimingWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                single_backend_time,
                                batch_size,
                                backend_time != maxInt64)                                               AS `quantiles_ttfb_state`,
        quantilesExactWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                single_backend_time,
                                batch_size,
                                backend_time != maxInt64)                                               AS `quantiles_ttfb_exact_state`,
        quantilesTimingWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                toUInt64(single_unload_time / 100),
                                batch_size,
                                unload_time != maxInt64)                                                AS `quantiles_unload_time_large_state`,
        quantilesTimingWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                single_unload_time,
                                batch_size,
                                unload_time != maxInt64)                                                AS `quantiles_unload_time_state`,
        quantilesExactWeightedStateIf(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99)(
                                single_unload_time,
                                batch_size,
                                unload_time != maxInt64)                                                AS `quantiles_unload_time_exact_state`,
        sumState(batch_size)                                                                               AS `sum_beacon_count_state`,
        sumState(error_count)                                                                              AS `sum_beacon_error_count_state`,
        sumStateIf(batch_size, http_call_status LIKE '1%')                                                 AS `sum_http1xx_state`,
        sumStateIf(batch_size, http_call_status LIKE '2%')                                                 AS `sum_http2xx_state`,
        sumStateIf(batch_size, http_call_status LIKE '3%')                                                 AS `sum_http3xx_state`,
        sumStateIf(batch_size, http_call_status LIKE '4%')                                                 AS `sum_http4xx_state`,
        sumStateIf(batch_size, http_call_status LIKE '5%')                                                 AS `sum_http5xx_state`,
        sumStateIf(batch_size, lowerUTF8(http_call_method) = 'delete')                                     AS `sum_http_delete_state`,
        sumStateIf(batch_size, lowerUTF8(http_call_method) = 'get')                                        AS `sum_http_get_state`,
        sumStateIf(batch_size, lowerUTF8(http_call_method) = 'post')                                       AS `sum_http_post_state`,
        sumStateIf(batch_size, lowerUTF8(http_call_method) = 'put')                                        AS `sum_http_put_state`
    FROM shared.website_monitoring_beacons
    GROUP BY client_id,
        type,
        t,
        website_id,
        browser_name,
        cache_interaction,
        custom_event_name,
        connection_type,
        error_id,
        error_type,
        country,
        country_code,
        continent,
        continent_code,
        subdivision,
        graphql_operation_name,
        http_call_origin,
        os_name,
        page,
        resource_type,
        notEmpty(user_id_or_session_id);
    ```
- Create distributed table  
    ```sql
    CREATE TABLE IF NOT EXISTS shared.all_website_monitoring_beacons_aggregated_1m   ON CLUSTER groupby_test (
        client_id                                           LowCardinality(String),
        t                                                   UInt64,
        type                                                LowCardinality(String),
        browser_name                                        LowCardinality(String),
        cache_interaction                                   LowCardinality(String),
        custom_event_name                                   LowCardinality(String),
        connection_type                                     LowCardinality(String),
        error_id                                            LowCardinality(String),
        error_type                                          LowCardinality(String),
        country                                             LowCardinality(String),
        country_code                                        LowCardinality(String),
        continent                                           LowCardinality(String),
        continent_code                                      LowCardinality(String),
        subdivision                                         LowCardinality(String),
        graphql_operation_name                              LowCardinality(String),
        http_call_origin                                    LowCardinality(String),
        os_name                                             LowCardinality(String),
        page                                                LowCardinality(String),
        resource_type                                       LowCardinality(String),
        website_id                                          LowCardinality(String),
        has_user_id_or_session_id                           UInt8,
        distinct_count_unique_users_or_sessions_state       AggregateFunction(uniq, String),
        max_app_cache_time_state                            AggregateFunction(max, UInt64),
        max_beacon_duration_state                           AggregateFunction(max, UInt64),
        max_children_time_state                             AggregateFunction(max, UInt64),
        max_cumulative_layout_shift_state                   AggregateFunction(max, UInt64),
        max_decoded_body_size_state                         AggregateFunction(max, UInt64),
        max_dns_time_state                                  AggregateFunction(max, UInt64),
        max_dom_time_state                                  AggregateFunction(max, UInt64),
        max_encoded_body_size_state                         AggregateFunction(max, UInt64),
        max_first_contentful_paint_time_state               AggregateFunction(max, UInt64),
        max_first_input_delay_state                         AggregateFunction(max, UInt64),
        max_first_paint_time_state                          AggregateFunction(max, UInt64),
        max_largest_contentful_paint_time_state             AggregateFunction(max, UInt64),
        max_redirect_time_state                             AggregateFunction(max, UInt64),
        max_request_time_state                              AggregateFunction(max, UInt64),
        max_response_time_state                             AggregateFunction(max, UInt64),
        max_ssl_time_state                                  AggregateFunction(max, UInt64),
        max_tcp_time_state                                  AggregateFunction(max, UInt64),
        max_transfer_size_state                             AggregateFunction(max, UInt64),
        max_ttfb_state                                      AggregateFunction(max, UInt64),
        max_unload_time_state                               AggregateFunction(max, UInt64),
        count_app_cache_time_state                          AggregateFunction(sum, UInt64),
        sum_app_cache_time_state                            AggregateFunction(sum, UInt64),
        count_beacon_duration_state                         AggregateFunction(sum, UInt64),
        sum_beacon_duration_state                           AggregateFunction(sum, UInt64),
        count_children_time_state                           AggregateFunction(sum, UInt64),
        sum_children_time_state                             AggregateFunction(sum, UInt64),
        count_cumulative_layout_shift_state                 AggregateFunction(sum, UInt64),
        sum_cumulative_layout_shift_state                   AggregateFunction(sum, UInt64),
        count_decoded_body_size_state                       AggregateFunction(sum, UInt64),
        sum_decoded_body_size_state                         AggregateFunction(sum, UInt64),
        count_dns_time_state                                AggregateFunction(sum, UInt64),
        sum_dns_time_state                                  AggregateFunction(sum, UInt64),
        count_dom_time_state                                AggregateFunction(sum, UInt64),
        sum_dom_time_state                                  AggregateFunction(sum, UInt64),
        count_encoded_body_size_state                       AggregateFunction(sum, UInt64),
        sum_encoded_body_size_state                         AggregateFunction(sum, UInt64),
        count_first_contentful_paint_time_state             AggregateFunction(sum, UInt64),
        sum_first_contentful_paint_time_state               AggregateFunction(sum, UInt64),
        count_first_input_delay_state                       AggregateFunction(sum, UInt64),
        sum_first_input_delay_state                         AggregateFunction(sum, UInt64),
        count_first_paint_time_state                        AggregateFunction(sum, UInt64),
        sum_first_paint_time_state                          AggregateFunction(sum, UInt64),
        count_largest_contentful_paint_time_state           AggregateFunction(sum, UInt64),
        sum_largest_contentful_paint_time_state             AggregateFunction(sum, UInt64),
        count_redirect_time_state                           AggregateFunction(sum, UInt64),
        sum_redirect_time_state                             AggregateFunction(sum, UInt64),
        count_request_time_state                            AggregateFunction(sum, UInt64),
        sum_request_time_state                              AggregateFunction(sum, UInt64),
        count_response_time_state                           AggregateFunction(sum, UInt64),
        sum_response_time_state                             AggregateFunction(sum, UInt64),
        count_ssl_time_state                                AggregateFunction(sum, UInt64),
        sum_ssl_time_state                                  AggregateFunction(sum, UInt64),
        count_tcp_time_state                                AggregateFunction(sum, UInt64),
        sum_tcp_time_state                                  AggregateFunction(sum, UInt64),
        count_transfer_size_state                           AggregateFunction(sum, UInt64),
        sum_transfer_size_state                             AggregateFunction(sum, UInt64),
        count_ttfb_state                                    AggregateFunction(sum, UInt64),
        sum_ttfb_state                                      AggregateFunction(sum, UInt64),
        count_unload_time_state                             AggregateFunction(sum, UInt64),
        sum_unload_time_state                               AggregateFunction(sum, UInt64),
        min_app_cache_time_state                            AggregateFunction(min, UInt64),
        min_children_time_state                             AggregateFunction(min, UInt64),
        min_cumulative_layout_shift_state                   AggregateFunction(min, UInt64),
        min_decoded_body_size_state                         AggregateFunction(min, UInt64),
        min_dns_time_state                                  AggregateFunction(min, UInt64),
        min_dom_time_state                                  AggregateFunction(min, UInt64),
        min_encoded_body_size_state                         AggregateFunction(min, UInt64),
        min_first_contentful_paint_time_state               AggregateFunction(min, UInt64),
        min_first_input_delay_state                         AggregateFunction(min, UInt64),
        min_first_paint_time_state                          AggregateFunction(min, UInt64),
        min_largest_contentful_paint_time_state             AggregateFunction(min, UInt64),
        min_redirect_time_state                             AggregateFunction(min, UInt64),
        min_request_time_state                              AggregateFunction(min, UInt64),
        min_response_time_state                             AggregateFunction(min, UInt64),
        min_ssl_time_state                                  AggregateFunction(min, UInt64),
        min_tcp_time_state                                  AggregateFunction(min, UInt64),
        min_transfer_size_state                             AggregateFunction(min, UInt64),
        min_ttfb_state                                      AggregateFunction(min, UInt64),
        min_unload_time_state                               AggregateFunction(min, UInt64),
        quantiles_app_cache_time_large_state                AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_app_cache_time_state                      AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_app_cache_time_exact_state                AggregateFunction(quantilesExactWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_beacon_duration_large_state               AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_beacon_duration_state                     AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_beacon_duration_exact_state               AggregateFunction(quantilesExactWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_children_time_large_state                 AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_children_time_state                       AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_children_time_exact_state                 AggregateFunction(quantilesExactWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_cumulative_layout_shift_large_state       AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_cumulative_layout_shift_state             AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_cumulative_layout_shift_exact_state       AggregateFunction(quantilesExactWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_decoded_body_size_large_state             AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_decoded_body_size_state                   AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_decoded_body_size_exact_state             AggregateFunction(quantilesExactWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_dns_time_large_state                      AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_dns_time_state                            AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_dns_time_exact_state                      AggregateFunction(quantilesExactWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_dom_time_large_state                      AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_dom_time_state                            AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_dom_time_exact_state                      AggregateFunction(quantilesExactWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_encoded_body_size_large_state             AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_encoded_body_size_state                   AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_encoded_body_size_exact_state             AggregateFunction(quantilesExactWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_first_contentful_paint_time_large_state   AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_first_contentful_paint_time_state         AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_first_contentful_paint_time_exact_state   AggregateFunction(quantilesExactWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_first_input_delay_large_state             AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_first_input_delay_state                   AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_first_input_delay_exact_state             AggregateFunction(quantilesExactWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_first_paint_time_large_state              AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_first_paint_time_state                    AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_first_paint_time_exact_state              AggregateFunction(quantilesExactWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_largest_contentful_paint_time_large_state AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_largest_contentful_paint_time_state       AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_largest_contentful_paint_time_exact_state AggregateFunction(quantilesExactWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_redirect_time_large_state                 AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_redirect_time_state                       AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_redirect_time_exact_state                 AggregateFunction(quantilesExactWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_request_time_large_state                  AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_request_time_state                        AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_request_time_exact_state                  AggregateFunction(quantilesExactWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_response_time_large_state                 AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_response_time_state                       AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_response_time_exact_state                 AggregateFunction(quantilesExactWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_ssl_time_large_state                      AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_ssl_time_state                            AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_ssl_time_exact_state                      AggregateFunction(quantilesExactWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_tcp_time_large_state                      AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_tcp_time_state                            AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_tcp_time_exact_state                      AggregateFunction(quantilesExactWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_transfer_size_large_state                 AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_transfer_size_state                       AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_transfer_size_exact_state                 AggregateFunction(quantilesExactWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_ttfb_large_state                          AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_ttfb_state                                AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_ttfb_exact_state                          AggregateFunction(quantilesExactWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_unload_time_large_state                   AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_unload_time_state                         AggregateFunction(quantilesTimingWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        quantiles_unload_time_exact_state                   AggregateFunction(quantilesExactWeighted(0.25, 0.5, 0.75, 0.9, 0.95, 0.98, 0.99), UInt64, UInt64),
        sum_beacon_count_state                              AggregateFunction(sum, UInt64),
        sum_beacon_error_count_state                        AggregateFunction(sum, UInt64),
        sum_http1xx_state                                   AggregateFunction(sum, UInt64),
        sum_http2xx_state                                   AggregateFunction(sum, UInt64),
        sum_http3xx_state                                   AggregateFunction(sum, UInt64),
        sum_http4xx_state                                   AggregateFunction(sum, UInt64),
        sum_http5xx_state                                   AggregateFunction(sum, UInt64),
        sum_http_delete_state                               AggregateFunction(sum, UInt64),
        sum_http_get_state                                  AggregateFunction(sum, UInt64),
        sum_http_post_state                                 AggregateFunction(sum, UInt64),
        sum_http_put_state                                  AggregateFunction(sum, UInt64)
    )
    ENGINE = Distributed('groupby_test', shared, website_monitoring_beacons_aggregated_1m_mv);
    ```

    ```sql
    ALTER TABLE shared.all_website_monitoring_beacons_aggregated_1m  ON CLUSTER groupby_test 
        ADD COLUMN IF NOT EXISTS min_beacon_duration_state AggregateFunction(min, UInt64);


    ALTER TABLE shared.all_website_monitoring_beacons_aggregated_1m  ON CLUSTER groupby_test 
        ADD COLUMN IF NOT EXISTS `min_ingestion_time_state` SimpleAggregateFunction(min, UInt64),
        ADD COLUMN IF NOT EXISTS `max_ingestion_time_state` SimpleAggregateFunction(max, UInt64),
        ADD COLUMN IF NOT EXISTS `min_timestamp_state`      SimpleAggregateFunction(min, UInt64);
    ```
- Insert data  
    ```sql
    INSERT INTO shared.website_monitoring_beacons (client_id,sample_multiplicity,website_id,page,phase,`timestamp`,duration,batch_size,accurate_timings_available,deprecations,page_load_id,beacon_id,backend_trace_id,`type`,custom_event_name,`meta.key`,`meta.value`,location_url,location_origin,location_path,error_count,error_message,error_id,stack_trace,component_stack,user_ip,user_id,user_name,user_email,user_languages,device_type,browser_name,browser_version,os_name,os_version,window_hidden,window_width,window_height,latitude,longitude,city,country,continent,http_call_url,http_call_origin,http_call_path,http_call_method,http_call_status,http_call_correlation_attempted,http_call_asynchronous,initiator,resource_type,cache_interaction,encoded_body_size,decoded_body_size,transfer_size,unload_time,redirect_time,app_cache_time,dns_time,tcp_time,ssl_time,request_time,response_time,processing_time,on_load_time,backend_time,frontend_time,dom_time,children_time,first_paint_time,first_contentful_paint_time,error_type,subdivision,accuracy_radius,subdivision_code,country_code,continent_code,ingestion_time,connection_type,stack_trace_parsing_status,`parsed_stack_trace.file`,`parsed_stack_trace.name`,`parsed_stack_trace.line`,`parsed_stack_trace.column`,`parsed_stack_trace.translation_status`,stack_trace_readability,clock_skew,csp_blocked_uri,csp_effective_directive,csp_original_policy,csp_disposition,csp_sample,csp_source_file,csp_line_number,csp_column_number,`parsed_stack_trace.translation_explanation`,session_id,largest_contentful_paint_time,first_input_delay_time,cumulative_layout_shift,graphql_operation_name,graphql_operation_type,snippet_version,`header.key`,`header.value`) VALUES ('local_instana_local',1,'n6PCzFGORAy67pVVzyjCog','created-recipes','pageLoad',1645519669776,1742,1,1,[],'219a27c78ed740b7','219a27c78ed740b7','','pageLoad','',[],[],'http://rumattach1.fyre.ibm.com:3380/simple/dojoget.html','http://rumattach1.fyre.ibm.com:3380','/simple/dojoget.html',0,'','','','','','','','',['en-US','en'],'','Firefox','97','Mac OS X','10',0,1688,603,'-1.0','-1.0','','','','','','','','-1',0,0,'html','document','',9223372036854775807,9223372036854775807,9223372036854775807,2,0,43,2,246,0,254,0,1187,1,555,1195,1181,7,9223372036854775807,9223372036854775807,'','',9223372036854775807,'','','',1645519746883,'',0,[],[],[],[],[],0,75365,'','','','','','',9223372036854775807,9223372036854775807,[],'1c6e03583e59d20b',9223372036854775807,4,9223372036854775807,'','','2',[],[]);

    INSERT INTO shared.website_monitoring_beacons (client_id,sample_multiplicity,website_id,page,phase,`timestamp`,duration,batch_size,accurate_timings_available,deprecations,page_load_id,beacon_id,backend_trace_id,`type`,custom_event_name,`meta.key`,`meta.value`,location_url,location_origin,location_path,error_count,error_message,error_id,stack_trace,component_stack,user_ip,user_id,user_name,user_email,user_languages,device_type,browser_name,browser_version,os_name,os_version,window_hidden,window_width,window_height,latitude,longitude,city,country,continent,http_call_url,http_call_origin,http_call_path,http_call_method,http_call_status,http_call_correlation_attempted,http_call_asynchronous,initiator,resource_type,cache_interaction,encoded_body_size,decoded_body_size,transfer_size,unload_time,redirect_time,app_cache_time,dns_time,tcp_time,ssl_time,request_time,response_time,processing_time,on_load_time,backend_time,frontend_time,dom_time,children_time,first_paint_time,first_contentful_paint_time,error_type,subdivision,accuracy_radius,subdivision_code,country_code,continent_code,ingestion_time,connection_type,stack_trace_parsing_status,`parsed_stack_trace.file`,`parsed_stack_trace.name`,`parsed_stack_trace.line`,`parsed_stack_trace.column`,`parsed_stack_trace.translation_status`,stack_trace_readability,clock_skew,csp_blocked_uri,csp_effective_directive,csp_original_policy,csp_disposition,csp_sample,csp_source_file,csp_line_number,csp_column_number,`parsed_stack_trace.translation_explanation`,session_id,largest_contentful_paint_time,first_input_delay_time,cumulative_layout_shift,graphql_operation_name,graphql_operation_type,snippet_version,`header.key`,`header.value`) VALUES ('local_instana_local',1,'n6PCzFGORAy67pVVzyjCog','created-recipes','pageLoad',1645519670380,554,1,1,[],'219a27c78ed740b7','a25b8fc1c2e49b90','','resourceLoad','',[],[],'http://rumattach1.fyre.ibm.com:3380/simple/dojoget.html','http://rumattach1.fyre.ibm.com:3380','/simple/dojoget.html',0,'','','','','','','','',['en-US','en'],'','Firefox','97','Mac OS X','10',0,1688,603,'-1.0','-1.0','','','','http://rumattach1.fyre.ibm.com:3380/libs/popper.min.js','http://rumattach1.fyre.ibm.com:3380','/libs/popper.min.js','GET','-1',0,1,'script','javascript','fullLoad',7510,21257,7906,9223372036854775807,9223372036854775807,19,2,258,9223372036854775807,272,9223372036854775807,9223372036854775807,9223372036854775807,554,9223372036854775807,9223372036854775807,9223372036854775807,9223372036854775807,9223372036854775807,'','',9223372036854775807,'','','',1645519746883,'',0,[],[],[],[],[],0,76504,'','','','','','',9223372036854775807,9223372036854775807,[],'',9223372036854775807,9223372036854775807,9223372036854775807,'','','2',[],[]);

    ```         

- Run Select  
    ```sql
    SELECT page AS `group_by_column_alias`,
        (sumMergeIf(sum_beacon_duration_state, 
            (toLowCardinality(equals(type, 'pageLoad'))))
            /sumMergeIf(count_beacon_duration_state, (toLowCardinality(equals(type, 'pageLoad'))))) AS `onLoadTimeAgg`,
        sumMergeIf(sum_beacon_count_state, 
            ((toLowCardinality(equals(type, 'pageLoad')) OR toLowCardinality(equals(type, 'pageChange'))))) AS `pageViewsAgg`,
        sumMergeIf(sum_beacon_error_count_state, (toLowCardinality(equals(type, 'error')))) AS `errorsAgg`,
        MIN(min_timestamp_state) AS `min_timestamp`,
        1640247100690 AS `metric_timestamp_alias`
    FROM shared.all_website_monitoring_beacons_aggregated_1m
    GROUP BY 
        `group_by_column_alias`,
        `metric_timestamp_alias`
    LIMIT 20
    ```
- Result   
    ```
    ┌─group_by_column_alias─┬─onLoadTimeAgg─┬─pageViewsAgg─┬─errorsAgg─┬─min_timestamp─┬─metric_timestamp_alias─┐
    │ created-recipes       │          1742 │            1 │         0 │ 1645519669776 │          1640247100690 │
    └───────────────────────┴───────────────┴──────────────┴───────────┴───────────────┴────────────────────────┘
    ```



error when using debug version. 
```
Received exception from server (version 22.3.1):
Code: 253. DB::Exception: Received from localhost:9000. DB::Exception: There was an error on [9.30.230.135:9000]: Code: 253. DB::Exception: Replica /ClickHouse/test3/tables/s1/t3/replicas/r1 already exists. (REPLICA_IS_ALREADY_EXIST) (version 21.12.1.1). (REPLICA_IS_ALREADY_EXIST)

```
