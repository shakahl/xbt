g++ -g -I ../misc -I . -O3 -o xbt_tracker_debug *.cpp ../misc/*.cpp ../misc/sql/*.cpp `mysql_config --libs`
