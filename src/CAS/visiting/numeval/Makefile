ifndef root
    include $(dir $(lastword $(MAKEFILE_LIST)))../Makefile
    $(call set_default_goal,CASVISITINGNUMEVAL)
else
    $(call make_so,CASVISITINGNUMEVAL,castlecasvisitingnumeval)
endif
