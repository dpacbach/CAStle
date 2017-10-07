ifndef root
    include $(dir $(lastword $(MAKEFILE_LIST)))../Makefile
else
    $(call set_location,CAS)
    # Must enter in order of dependencies.
    locations := utils number expr creation visitors reduction
    $(call enter_all,$(locations))
endif
