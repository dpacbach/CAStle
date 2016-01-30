ifndef TOPLEVELWD
    include $(dir $(lastword $(MAKEFILE_LIST)))../makefile
    $(call set_default_goal,PARSERSDEFAULT)
else
    $(call make_so,PARSERSDEFAULT,castleparsersdefault)
endif
