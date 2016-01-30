ifndef TOPLEVELWD
    include $(dir $(lastword $(MAKEFILE_LIST)))../makefile
    $(call set_default_goal,PARSERDEFAULT)
else
    $(call make_so,TOKENS,castleparsersdefault)
endif
