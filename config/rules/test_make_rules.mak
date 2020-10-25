 ########################################################-*-mode:Makefile-*-
 ##                                                                       ##
 ##                Centre for Speech Technology Research                  ##
 ##                     University of Edinburgh, UK                       ##
 ##                       Copyright (c) 1996,1997                         ##
 ##                        All Rights Reserved.                           ##
 ##                                                                       ##
 ##  Permission is hereby granted, free of charge, to use and distribute  ##
 ##  this software and its documentation without restriction, including   ##
 ##  without limitation the rights to use, copy, modify, merge, publish,  ##
 ##  distribute, sublicense, and/or sell copies of this work, and to      ##
 ##  permit persons to whom this work is furnished to do so, subject to   ##
 ##  the following conditions:                                            ##
 ##   1. The code must retain the above copyright notice, this list of    ##
 ##      conditions and the following disclaimer.                         ##
 ##   2. Any modifications must be clearly marked as such.                ##
 ##   3. Original authors' names are not deleted.                         ##
 ##   4. The authors' names are not used to endorse or promote products   ##
 ##      derived from this software without specific prior written        ##
 ##      permission.                                                      ##
 ##                                                                       ##
 ##  THE UNIVERSITY OF EDINBURGH AND THE CONTRIBUTORS TO THIS WORK        ##
 ##  DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING      ##
 ##  ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT   ##
 ##  SHALL THE UNIVERSITY OF EDINBURGH NOR THE CONTRIBUTORS BE LIABLE     ##
 ##  FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES    ##
 ##  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN   ##
 ##  AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,          ##
 ##  ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF       ##
 ##  THIS SOFTWARE.                                                       ##
 ##                                                                       ##
 ###########################################################################
 #              Makefile rules for testing things                          #
 ###########################################################################

TEST_PROGRAMS = $(TEST_MODULES:%=%_example) $(TEST_MODULES:%=%_regression)
TSRCS = $(TEST_PROGRAMS:%=%.cc)
SRCS = $(TSRCS)
OBJS = $(SRCS:%.cc=%.o)
SCRIPTS = $(TEST_SCRIPTS:%=%.sh)
FILES = Makefile \
	$(SRCS) \
	$(SCRIPTS) \
        $(OTHERS)

LOCAL_DEFINES += -DDATA="\"$(DATA)\""

include $(TOP)/config/common_make_rules

test_scripts: $(TEST_SCRIPTS:%=%_script_test)

test_modules: $(PROJECT_LIBDEPS) $(TEST_MODULES:%=%_module_build_and_test) 

just_test_scripts: test_scripts

just_test_modules: $(TEST_MODULES:%=%_module_test) 


$(TEST_MODULES:%=%_module_build_and_test) : %_module_build_and_test :  %_module_rebuild %_module_test

$(TEST_MODULES:%=%_module_rebuild) : %_module_rebuild : 
	@echo 'build $* (module)'
	@$(RM) -f $(OBJS)
	@if $(MAKE) --no-print-directory PROJECT_LIBDEPS= OPTIMISE=$(TEST_OPTIMISE) WARN=1 $*_example $*_regression ;\
		then \
		: ;\
	else \
		echo $* example status: FAILED ; exit 1	;\
	fi

$(TEST_MODULES:%=%_module_test) : %_module_test : correct/%_example.out correct/%_regression.out 
	@echo 'test $* (module)'
	@LD_LIBRARY_PATH='$(TOP)/lib:$(LD_LIBRARY_PATH)' ; export LD_LIBRARY_PATH;\
	if ./$*_example $($(*:=_example_args)) > $*_example.out ;\
		then \
		echo $*_example completed ;\
		if [ ! -f $*_example.out ] || diff correct/$*_example.out $*_example.out ;\
			then \
			echo $* example status: CORRECT ;\
		else \
			echo $* example status: INCORRECT ;\
		fi ;\
	else \
		echo $* example status: FAILED ;\
	fi ;\
	if ./$*_regression $($(*:=_regression_args)) > $*_regression.out ;\
		then \
		echo $*_regression completed ;\
		if [ ! -f $*_regression.out ] || diff correct/$*_regression.out $*_regression.out ;\
			then \
			echo $* regression status: CORRECT ;\
		else \
			echo $* regression status: INCORRECT ;\
		fi ;\
	else \
		echo $* regression status: FAILED ;\
	fi
	@echo
	@echo

$(TEST_SCRIPTS:%=%_script_test) : %_script_test : %.sh correct/%_script.out
	@echo 'test $* (script)'
	@OUTPUT='$*_script.out'  ;\
	TOP='$(TOP)' ;\
	export TOP OUTPUT ;\
	LD_LIBRARY_PATH='$(TOP)/lib:$(LD_LIBRARY_PATH)' ; export LD_LIBRARY_PATH;\
	if /bin/sh $*.sh $($(*:=_script_args)) ;\
	then \
		echo $* script completed ;\
		if [ ! -f $*_script.out ] || diff correct/$*_script.out $*_script.out ;\
			then \
			echo $* script status: CORRECT ;\
		else \
			echo $* script status: INCORRECT ;\
		fi ;\
	else \
		echo $* script status: FAILED ;\
	fi
	@echo
	@echo

$(SRCS:%.cc=%.o) : %.o : %.cc

TEMPS = $(wildcard *_temp.cc) 

$(TEMPS:%.cc=%.o) : %.o : %.cc


% : %.o $(PROJECT_LIBDEPS)
	$(LINK_COMMAND) -o $@ $@.o $($(@:=_LIBS)) $(LIBS)


