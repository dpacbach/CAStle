ifndef root
    include $(dir $(lastword $(MAKEFILE_LIST)))../Makefile
else
    $(call make_so,CASVISITORSRENDERING,castlecasvisitorsrendering)

    locations := infix
    $(call enter_all,$(locations))
endif
