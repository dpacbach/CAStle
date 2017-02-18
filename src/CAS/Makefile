ifndef root
    include $(dir $(lastword $(MAKEFILE_LIST)))../Makefile
    #$(call set_default_goal,)
else
    $(call set_location,CAS)
    # In general, must enter in order of dependencies.
    locations := utils number expr creation visiting reduction
    $(call enter_all,$(locations))
endif
