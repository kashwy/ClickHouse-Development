# ClickHouse-Development

type $env:USERPROFILE\.ssh\id_rsa.pub | ssh root@ip  "cat >> .ssh/authorized_keys"

type $env:USERPROFILE\.ssh\id_rsa.pub | ssh root@ip  "cat >> .ssh/authorized_keys"


 

subscription

Test

  ssh root@ubuntu_fyre


~clickhouse-server start


start server: 

$ cd ~/src/ClibMouse/ClickHouse/programs/server

$ ~/src/ClibMouse/ClickHouse/build/programs/clickhouse-server start



~/src/ClickHouse/build/programs/clickhouse-server start

~/src/ClibMouse2/ClickHouse/build/programs/clickhouse-server start


$ cd ~/src/ClickHouse/programs/server
$ ~/src/ClickHouse/build/programs/clickhouse-server start
$ ~/src/kashwy/ClickHouse_test_git/ClickHouse/build/programs/clickhouse-server start

run client in another terminal:
$ ~/src/ClickHouse/build/programs/clickhouse client
SELECT version()
~/src/kashwy/ClickHouse_test_git/ClickHouse/build/programs/clickhouse client

~/src/ClickHouse/build/programs/clickhouse-local



git mergetool 

 solve submodule conflict

chose option for  {local}: 


gdb:

b 


git clone --recursive git@github.com:DevTeamBK/ClickHouse.git

git clone --recursive git@github.com:ClibMouse/ClickHouse.git



sudo /usr/sbin/update-ccache-symlinks
export PATH="/usr/lib/ccache/:$PATH"

export CC=clang-14
export CXX=clang++-14

export CC=clang-15
export CXX=clang++-15

xx--cmake .. -DCMAKE_BUILD_TYPE=Debug -DENABLE_TESTS=1 -DENABLE_CLICKHOUSE_SELF_EXTRACTING=OFF -DUSE_STATIC_LIBRARIES=0 -DSPLIT_SHARED_LIBRARIES=1 -DFLATBUFFERS_BUILD_SHAREDLIB=1 -DGLIBC_COMPATIBILITY=0  


cmake .. -DCMAKE_BUILD_TYPE=Debug -DENABLE_TESTS=1 -DENABLE_CLICKHOUSE_SELF_EXTRACTING=OFF  -DGLIBC_COMPATIBILITY=0  

xx--cmake .. -DCMAKE_BUILD_TYPE=Debug -DENABLE_TESTS=1 -DENABLE_CLICKHOUSE_SELF_EXTRACTING=OFF -DUSE_STATIC_LIBRARIES=0 -DSPLIT_SHARED_LIBRARIES=1      -DCLICKHOUSE_SPLIT_BINARY=1      -DENABLE_CLICKHOUSE_SU=OFF
ninja -j 8



unit test

src/unit_tests_dbms --gtest_filter="ParserKQLQuery*"


src/unit_tests_dbms --gtest_filter="ParserKQLQuery*" --gtest_brief=1


            "print dynamic(parse_ipv4('127.0.0.1'))",
            "throws"

./programs/clickhouse-local "--multiquery" --dialect='kusto_auto'

./programs/clickhouse-local "--multiquery" --dialect='kusto'

./programs/clickhouse-client "--multiquery" --dialect='kusto_auto'


functional test:


$ ~/src/ClibMouse/ClickHouse/build/programs/clickhouse-server start

-- cd ~/src/ClibMouse/ClickHouse/tests

./clickhouse-test -c "../build/programs/clickhouse-client"  02366_kql_operator_in_sql.sql


in folder :  ~/src/ClibMouse/ClickHouse

tests/clickhouse-test -b build/programs/clickhouse -c build/programs/clickhouse-client --zookeeper --shard --configserver programs/server/config.xml --configclient programs/client/clickhouse-client.xml 02366_kql_func_general.sql

----------------------------->

/root/src/ClibMouse-OSS/ClickHouse/tests

./clickhouse-test -b ../build/programs/clickhouse -c ../build/programs/clickhouse-client --zookeeper --shard --configserver ../programs/server/config.xml --configclient ../programs/client/clickhouse-client.xml 02366_kql

//--------------------------------------------------------------------------------
How to shutdown clickhouse instance

systemctl stop clickhouse-server




Steps to execute the script
cd utils/check-style

Comment out the line#142 to remove python files audit from style-check

./check-style

./fix-style


 apt install systemd-coredump


//--------------------------------------------------------------------------------

INSERT INTO StormEvents FROM INFILE '../StormEvents.csv' FORMAT CSV;


cat ../data/db_sample_events_1000.json | build/clickhouse-client --QUERY="INSERT INTO kql.events FORMAT JSONEachRow";


/opt/clickhouse/bin/clickhouse-client  --query="INSERT INTO StormEvents FORMAT CSV" < StormEvents.csv
//--------------------------------------------------------------------------------




https://askubuntu.com/questions/470545/how-do-i-set-up-ccache



use ccache:

sudo apt install ccache
sudo /usr/sbin/update-ccache-symlinks
export PATH="/usr/lib/ccache/:$PATH"
which clang-14


Just run clickhouse-client with -m switch, and it starts executing only after you finish the line with a semicolon.

disable all unneeded libraries (with -D ENABLE_xxx=0 in cmake); examples: LLVM, Hyperscan;





sudo clickhouse start


cp -a ./programs/. /root/demo/clickhouse/



    auto npos = pos;
    int i = 0;
    while (!npos->isEnd() && npos->type != TokenType::PipeMark && npos->type != TokenType::Semicolon)
    {
        std::cout<<i<<" - "<<String(npos->begin,npos->end)<<std::endl;
        i++;
        ++npos;
    }


install gdb from zip:


sudo apt-get update
sudo apt-get upgrade
sudo apt-get install libgmp-dev
wget http://ftp.gnu.org/gnu/gdb/gdb-12.1.tar.gz
tar -xvzf gdb-12.1.tar.gz
./configure
make
sudo make install


 mkdir -p /usr/local/share/gdb/python/gdb
 cp -rf gdb/python/lib/gdb/* /usr/local/share/gdb/python/gdb/


cp -a ClickHouse/. ClickHouse_bk_3/ 

cp -a ClickHouse/. ClickHouse_phase2/ 


Poco::toLower(name)
String function_name_lowercase = Poco::toLower(function_name);




SELECT * FROM view(SELECT name FROM months);

SELECT * FROM view(SELECT FirstName FROM Customers);

SELECT * FROM sqlite('/root/src/DevTeamBK/ClickHouse_phase2/sqlite/db1',tb1)


CREATE TABLE tmp ENGINE = Memory  AS view(SELECT FirstName FROM Customers);

CREATE TABLE tmp1 ENGINE = Memory  AS sqlite('/root/src/DevTeamBK/ClickHouse_phase2/sqlite/db1',tb1)


CREATE TABLE tmp4 ENGINE = Memory AS kql(Customers|project FirstName);

CREATE TABLE tmp3 ENGINE = Memory AS (Select * from Customers);




-exec p pos.tokens.data.size() 

-exec p pos.tokens[0]

-exec p pos.index 

-exec p pos.tokens[pos.index]

-exec p pos.tokens[0].lexer


unit test

src/unit_tests_dbms --gtest_filter="ParserKQLQuery*"

src/unit_tests_dbms --gtest_filter="ParserKQLQuery*" --gtest_brief=1


./programs/clickhouse-local "--multiquery" --dialect='kusto_auto'

./programs/clickhouse-client "--multiquery" --dialect='kusto_auto'

Customers | summarize cnt= count()+1,age= dcountif(Age,Age>20)+2  by name = strcat(FirstName,' ',substring(LastName,1,strlen(FirstName)-2)),hiage 



You can download clang 14 for with the instructions on the llvm page here:

wget https://apt.llvm.org/llvm.sh
chmod +x llvm.sh
sudo ./llvm.sh 14





cat ~/.ssh/id_rsa.pub 


StormEvents
| extend  duration = EndTime - StartTime
| where duration > 0s
| where duration < 100s
| summarize event_count = count()
    by bin(duration, 5m), State
| sort by duration asc
| summarize percentiles(duration, 5, 20, 50, 80, 95) by State



src/Interpreters/InterpreterDescribeQuery.cpp


Check your current version with:

cmake --version
Uninstall it with:

sudo apt remove cmake
Visit https://cmake.org/download/ and download the latest bash script.

In my case cmake-3.24.3-linux-x86_64.sh is sufficient.
Copy the script to /opt/.

Make the script executable:

chmod +x /opt/cmake-3.24.3-linux-x86_64.sh
Change to desired installation directory (to /opt/ for example)

As of cmake 3.10.2 the installer no longer seems to install to /opt by default
Run:

sudo bash /opt/cmake-3.24.3-linux-x86_64.sh
You will need to press y twice.

The script installs the binary to /opt/cmake-3.*your_version* so in order to get the cmake command, make a symbolic link:

sudo ln -s /opt/cmake-3.24.3-linux-x86_64/bin/* /usr/local/bin


sudo ln -s /usr/local/bin/cmake /usr/bin/cmake

Test your results with:

cmake --version



~/src/ClibMouse-OSS/ClickHouse/build/programs/clickhouse-server start

 cd ~/src/ClibMouse-OSS/ClickHouse/tests

./clickhouse-test -c "../build/programs/clickhouse-client"  02366_kql_operator_in_sql.sql


./clickhouse-test -b build/programs/clickhouse -c build/programs/clickhouse-client --zookeeper --shard --configserver programs/server/config.xml --configclient programs/client/clickhouse-client.xml 02366_kql


./clickhouse-test -b ../build/programs/clickhouse -c ../build/programs/clickhouse-client --zookeeper --shard --configserver ../programs/server/config.xml --configclient ../programs/client/clickhouse-client.xml 02366_kql


./clickhouse-test  -c "../build/programs/clickhouse-client"  --configserver programs/server/config.xml --configclient programs/client/clickhouse-client.xml 02366_kql
