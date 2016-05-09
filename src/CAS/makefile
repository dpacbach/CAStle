ifndef TOPLEVELWD
    include $(dir $(lastword $(MAKEFILE_LIST)))../makefile
    #$(call set_default_goal,)
else
    $(call set_location,CAS)
    # In general, must enter in order of dependencies.
    locations := number expr
    $(call enter_all,$(locations))
endif
