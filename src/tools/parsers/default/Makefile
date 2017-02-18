ifndef root
    include $(dir $(lastword $(MAKEFILE_LIST)))../Makefile
    $(call set_default_goal,PARSERSDEFAULT)
else
    $(call make_so,PARSERSDEFAULT,castleparsersdefault)
endif
