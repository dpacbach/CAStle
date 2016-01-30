ifndef TOPLEVELWD
    include $(dir $(lastword $(MAKEFILE_LIST)))../Makefile
    #$(call set_default_goal,NBRS)
else
    # In general, must enter in order of dependencies.
    locations := numbers tools
    $(call enter_all,$(locations))
endif
