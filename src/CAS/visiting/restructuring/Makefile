ifndef root
    include $(dir $(lastword $(MAKEFILE_LIST)))../Makefile
    $(call set_default_goal,CASVISITINGRESTRUCTURING)
else
    $(call make_so,CASVISITINGRESTRUCTURING,castlecasvisitingrestructuring)
endif
