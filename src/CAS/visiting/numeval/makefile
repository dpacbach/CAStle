ifndef TOPLEVELWD
    include $(dir $(lastword $(MAKEFILE_LIST)))../makefile
    $(call set_default_goal,CASVISITINGNUMEVAL)
else
    $(call make_so,CASVISITINGNUMEVAL,castlecasvisitingnumeval)
endif
