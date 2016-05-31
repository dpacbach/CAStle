ifndef TOPLEVELWD
    include $(dir $(lastword $(MAKEFILE_LIST)))../makefile
    $(call set_default_goal,CASVISITINGRESTRUCTURING)
else
    $(call make_so,CASVISITINGRESTRUCTURING,castlecasvisitingrestructuring)
endif
