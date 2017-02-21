ifndef root
    include $(dir $(lastword $(MAKEFILE_LIST)))../Makefile
    $(call set_default_goal,)
else
    locations := numeval rendering restructuring
    $(call enter_all,$(locations))
endif
