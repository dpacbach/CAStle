ifndef TOPLEVELWD
    include $(dir $(lastword $(MAKEFILE_LIST)))../makefile
    $(call set_default_goal,MATRIX)
else
    # In general, must enter in order of dependencies.
    locations := matrix
    $(call enter_all,$(locations))
endif
