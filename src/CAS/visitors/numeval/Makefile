ifndef root
    include $(dir $(lastword $(MAKEFILE_LIST)))../Makefile
    $(call set_default_goal,CASVISITORSNUMEVAL)
else
    $(call make_so,CASVISITORSNUMEVAL,castlecasvisitorsnumeval)
endif
