ifndef root
    include $(dir $(lastword $(MAKEFILE_LIST)))../Makefile
    $(call set_default_goal,CASVISITORSRENDERINGINFIX)
else
    $(call make_so,CASVISITORSRENDERINGINFIX,castlecasvisitorsrenderinginfix)
endif
