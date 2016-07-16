ifndef TOPLEVELWD
    include $(dir $(lastword $(MAKEFILE_LIST)))../Makefile
    $(call set_default_goal,CLI)
else
    # In general, must enter in order of dependencies.
    locations := numbers tools CAS interface
    $(call enter_all,$(locations))

    $(call make_exe,CLI,castle)
endif
