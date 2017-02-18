ifndef root
    include $(dir $(lastword $(MAKEFILE_LIST)))../Makefile
    #$(call set_default_goal,)
else
    $(call set_location,TOOLS)
    # In general, must enter in order of dependencies.
    locations := matrix parsers
    $(call enter_all,$(locations))
endif
