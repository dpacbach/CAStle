ifndef root
    include $(dir $(lastword $(MAKEFILE_LIST)))../Makefile
    $(call set_default_goal,CASVISITORSRESTRUCTURING)
else
    $(call make_so,CASVISITORSRESTRUCTURING,castlecasvisitorsrestructuring)
endif
