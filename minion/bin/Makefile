FLAGS=-std=gnu++14 -Wall -Wextra -Wno-unused-parameter -Wno-sign-compare -I ../minion -I src/ -DWDEG -O3 -mdynamic-no-pic -fomit-frame-pointer -fPIC -DLIBMINION -MD -MP
CONSRCS=src/build_constraint_1.cpp src/build_constraint_2.cpp src/build_constraint_3.cpp src/build_constraint_4.cpp src/build_constraint_5.cpp src/build_constraint_6.cpp src/build_constraint_7.cpp src/build_constraint_8.cpp src/build_constraint_9.cpp src/build_constraint_10.cpp src/build_constraint_11.cpp src/build_constraint_12.cpp src/build_constraint_13.cpp src/build_constraint_14.cpp src/build_constraint_15.cpp src/build_constraint_16.cpp src/build_constraint_17.cpp src/BuildStaticStart.cpp
CONOBJS=bin/build_constraint_1.o bin/build_constraint_2.o bin/build_constraint_3.o bin/build_constraint_4.o bin/build_constraint_5.o bin/build_constraint_6.o bin/build_constraint_7.o bin/build_constraint_8.o bin/build_constraint_9.o bin/build_constraint_10.o bin/build_constraint_11.o bin/build_constraint_12.o bin/build_constraint_13.o bin/build_constraint_14.o bin/build_constraint_15.o bin/build_constraint_16.o bin/build_constraint_17.o bin/BuildStaticStart.o
MINLIBOBJS=bin/BuildVariables.o bin/BuildCSP.o bin/buildConstraints.o bin/commandline_parse.o bin/debug_functions.o bin/get_info.o bin/info_dumps.o bin/minion.o bin/globals.o bin/preprocess.o bin/trigger_timer.o bin/sha1.o bin/help.o bin/inputfile_parse.o bin/dump_state.o bin/parallel.o bin/preprocess_parallel.o bin/work_steal.o bin/search_dump.o bin/search_dump_sql.o bin/command_search.o bin/libwrapper.o
MINBINOBJS=bin/BuildVariables.o bin/BuildCSP.o bin/buildConstraints.o bin/commandline_parse.o bin/debug_functions.o bin/get_info.o bin/info_dumps.o bin/minion.o bin/globals.o bin/preprocess.o bin/trigger_timer.o bin/sha1.o bin/help.o bin/inputfile_parse.o bin/dump_state.o bin/parallel.o bin/preprocess_parallel.o bin/work_steal.o bin/search_dump.o bin/search_dump_sql.o bin/command_search.o bin/libwrapper.o bin/main.o
all: minion libminion.a
-include $(CONOBJS:.o=.d)
-include $(MINLIBOBJS:.o=.d)
-include $(MINBINOBJS:.o=.d)
bin/build_constraint_1.o: Makeflags.mak src/build_constraint_1.cpp
	 c++  $(FLAGS)  -c -o bin/build_constraint_1.o src/build_constraint_1.cpp
bin/build_constraint_2.o: Makeflags.mak src/build_constraint_2.cpp
	 c++  $(FLAGS)  -c -o bin/build_constraint_2.o src/build_constraint_2.cpp
bin/build_constraint_3.o: Makeflags.mak src/build_constraint_3.cpp
	 c++  $(FLAGS)  -c -o bin/build_constraint_3.o src/build_constraint_3.cpp
bin/build_constraint_4.o: Makeflags.mak src/build_constraint_4.cpp
	 c++  $(FLAGS)  -c -o bin/build_constraint_4.o src/build_constraint_4.cpp
bin/build_constraint_5.o: Makeflags.mak src/build_constraint_5.cpp
	 c++  $(FLAGS)  -c -o bin/build_constraint_5.o src/build_constraint_5.cpp
bin/build_constraint_6.o: Makeflags.mak src/build_constraint_6.cpp
	 c++  $(FLAGS)  -c -o bin/build_constraint_6.o src/build_constraint_6.cpp
bin/build_constraint_7.o: Makeflags.mak src/build_constraint_7.cpp
	 c++  $(FLAGS)  -c -o bin/build_constraint_7.o src/build_constraint_7.cpp
bin/build_constraint_8.o: Makeflags.mak src/build_constraint_8.cpp
	 c++  $(FLAGS)  -c -o bin/build_constraint_8.o src/build_constraint_8.cpp
bin/build_constraint_9.o: Makeflags.mak src/build_constraint_9.cpp
	 c++  $(FLAGS)  -c -o bin/build_constraint_9.o src/build_constraint_9.cpp
bin/build_constraint_10.o: Makeflags.mak src/build_constraint_10.cpp
	 c++  $(FLAGS)  -c -o bin/build_constraint_10.o src/build_constraint_10.cpp
bin/build_constraint_11.o: Makeflags.mak src/build_constraint_11.cpp
	 c++  $(FLAGS)  -c -o bin/build_constraint_11.o src/build_constraint_11.cpp
bin/build_constraint_12.o: Makeflags.mak src/build_constraint_12.cpp
	 c++  $(FLAGS)  -c -o bin/build_constraint_12.o src/build_constraint_12.cpp
bin/build_constraint_13.o: Makeflags.mak src/build_constraint_13.cpp
	 c++  $(FLAGS)  -c -o bin/build_constraint_13.o src/build_constraint_13.cpp
bin/build_constraint_14.o: Makeflags.mak src/build_constraint_14.cpp
	 c++  $(FLAGS)  -c -o bin/build_constraint_14.o src/build_constraint_14.cpp
bin/build_constraint_15.o: Makeflags.mak src/build_constraint_15.cpp
	 c++  $(FLAGS)  -c -o bin/build_constraint_15.o src/build_constraint_15.cpp
bin/build_constraint_16.o: Makeflags.mak src/build_constraint_16.cpp
	 c++  $(FLAGS)  -c -o bin/build_constraint_16.o src/build_constraint_16.cpp
bin/build_constraint_17.o: Makeflags.mak src/build_constraint_17.cpp
	 c++  $(FLAGS)  -c -o bin/build_constraint_17.o src/build_constraint_17.cpp
bin/BuildStaticStart.o: Makeflags.mak src/BuildStaticStart.cpp
	 c++  $(FLAGS)  -c -o bin/BuildStaticStart.o src/BuildStaticStart.cpp
bin/BuildVariables.o : Makeflags.mak ../minion/BuildVariables.cpp
	 c++  $(FLAGS)  -c -o bin/BuildVariables.o ../minion/BuildVariables.cpp
bin/BuildCSP.o : Makeflags.mak ../minion/BuildCSP.cpp
	 c++  $(FLAGS)  -c -o bin/BuildCSP.o ../minion/BuildCSP.cpp
bin/buildConstraints.o : Makeflags.mak ../minion/buildConstraints.cpp
	 c++  $(FLAGS)  -c -o bin/buildConstraints.o ../minion/buildConstraints.cpp
bin/commandline_parse.o : Makeflags.mak ../minion/commandline_parse.cpp
	 c++  $(FLAGS)  -c -o bin/commandline_parse.o ../minion/commandline_parse.cpp
bin/debug_functions.o : Makeflags.mak ../minion/debug_functions.cpp
	 c++  $(FLAGS)  -c -o bin/debug_functions.o ../minion/debug_functions.cpp
bin/get_info.o : Makeflags.mak ../minion/get_info.cpp
	 c++  $(FLAGS)  -c -o bin/get_info.o ../minion/get_info.cpp
bin/info_dumps.o : Makeflags.mak ../minion/info_dumps.cpp
	 c++  $(FLAGS)  -c -o bin/info_dumps.o ../minion/info_dumps.cpp
bin/minion.o : Makeflags.mak ../minion/minion.cpp
	 c++  $(FLAGS)  -c -o bin/minion.o ../minion/minion.cpp
bin/globals.o : Makeflags.mak ../minion/globals.cpp
	 c++  $(FLAGS)  -c -o bin/globals.o ../minion/globals.cpp
bin/preprocess.o : Makeflags.mak ../minion/preprocess.cpp
	 c++  $(FLAGS)  -c -o bin/preprocess.o ../minion/preprocess.cpp
bin/trigger_timer.o : Makeflags.mak ../minion/system/trigger_timer.cpp
	 c++  $(FLAGS)  -c -o bin/trigger_timer.o ../minion/system/trigger_timer.cpp
bin/sha1.o : Makeflags.mak ../minion/system/sha1.cpp
	 c++  $(FLAGS)  -c -o bin/sha1.o ../minion/system/sha1.cpp
bin/help.o : Makeflags.mak ../minion/help/help.cpp
	 c++  $(FLAGS)  -c -o bin/help.o ../minion/help/help.cpp
bin/inputfile_parse.o : Makeflags.mak ../minion/inputfile_parse/inputfile_parse.cpp
	 c++  $(FLAGS)  -c -o bin/inputfile_parse.o ../minion/inputfile_parse/inputfile_parse.cpp
bin/dump_state.o : Makeflags.mak ../minion/dump_state.cpp
	 c++  $(FLAGS)  -c -o bin/dump_state.o ../minion/dump_state.cpp
bin/parallel.o : Makeflags.mak ../minion/parallel.cpp
	 c++  $(FLAGS)  -c -o bin/parallel.o ../minion/parallel.cpp
bin/preprocess_parallel.o : Makeflags.mak ../minion/parallel/preprocess_parallel.cpp
	 c++  $(FLAGS)  -c -o bin/preprocess_parallel.o ../minion/parallel/preprocess_parallel.cpp
bin/work_steal.o : Makeflags.mak ../minion/parallel/work_steal.cpp
	 c++  $(FLAGS)  -c -o bin/work_steal.o ../minion/parallel/work_steal.cpp
bin/search_dump.o : Makeflags.mak ../minion/search_dump.cpp
	 c++  $(FLAGS)  -c -o bin/search_dump.o ../minion/search_dump.cpp
bin/search_dump_sql.o : Makeflags.mak ../minion/search_dump_sql.cpp
	 c++  $(FLAGS)  -c -o bin/search_dump_sql.o ../minion/search_dump_sql.cpp
bin/command_search.o : Makeflags.mak ../minion/command_search.cpp
	 c++  $(FLAGS)  -c -o bin/command_search.o ../minion/command_search.cpp
bin/libwrapper.o : Makeflags.mak ../minion/libwrapper.cpp
	 c++  $(FLAGS)  -c -o bin/libwrapper.o ../minion/libwrapper.cpp
bin/main.o : Makeflags.mak ../minion/main.cpp
	 c++  $(FLAGS)  -c -o bin/main.o ../minion/main.cpp
minion: $(CONOBJS) $(MINBINOBJS)
	 c++  $(FLAGS)  $(CONOBJS)  $(MINBINOBJS) -pthread -o minion
libminion.a: $(CONOBJS) $(MINLIBOBJS)
	ar rcs libminion.a $(MINLIBOBJS)  $(CONOBJS) 
test_multithread: libminion.a ../test_instances/test_multithread.cpp
	 c++  $(FLAGS)  ../test_instances/test_multithread.cpp -L. -lminion -pthread -o test_multithread
test_midsearch_basic: libminion.a ../test_instances/test_midsearch_basic.cpp
	 c++  $(FLAGS)  ../test_instances/test_midsearch_basic.cpp -L. -lminion -pthread -o test_midsearch_basic
test_reify_midsearch: libminion.a ../test_instances/test_reify_midsearch.cpp
	 c++  $(FLAGS)  ../test_instances/test_reify_midsearch.cpp -L. -lminion -pthread -o test_reify_midsearch
test: test_multithread test_midsearch_basic test_reify_midsearch
	./test_multithread
	./test_midsearch_basic
	./test_reify_midsearch
.PHONY: test
