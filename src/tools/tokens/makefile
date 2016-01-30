ifndef TOPLEVELWD
    include $(dir $(lastword $(MAKEFILE_LIST)))../makefile
    $(call set_default_goal,TOKENS)
else
    $(call make_so,TOKENS,castletokens)
endif
