ifndef root
    include $(dir $(lastword $(MAKEFILE_LIST)))../Makefile
    $(call set_default_goal,CASVISITINGRENDERING)
else
    $(call make_so,CASVISITINGRENDERING,castlecasvisitingrendering)

    locations := infix
    $(call enter_all,$(locations))
endif
