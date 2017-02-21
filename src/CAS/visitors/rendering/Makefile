ifndef root
    include $(dir $(lastword $(MAKEFILE_LIST)))../Makefile
    $(call set_default_goal,CASVISITORSRENDERING)
else
    $(call make_so,CASVISITORSRENDERING,castlecasvisitorsrendering)

    locations := infix
    $(call enter_all,$(locations))
endif
