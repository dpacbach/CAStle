ifndef TOPLEVELWD
    include $(dir $(lastword $(MAKEFILE_LIST)))../makefile
    $(call set_location,TOOLS)
    #$(call set_default_goal,)
else
    # In general, must enter in order of dependencies.
    locations := matrix token
    $(call enter_all,$(locations))
endif
