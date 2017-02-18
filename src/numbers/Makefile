ifndef root
    include $(dir $(lastword $(MAKEFILE_LIST)))../Makefile
    $(call set_default_goal,NBRS)
else
    #$(call make_exe,NBRS,perftest)
    $(call make_so,NBRS,numbers)
endif
