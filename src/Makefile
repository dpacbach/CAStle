ifndef root
    include $(dir $(lastword $(MAKEFILE_LIST)))../Makefile
else
    # Must enter in order of dependencies.
    locations := utils numbers parsers CAS interface
    $(call enter_all,$(locations))

    $(call make_exe,CLI,castle)
endif
