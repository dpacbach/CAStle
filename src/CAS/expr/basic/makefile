ifndef TOPLEVELWD
    include $(dir $(lastword $(MAKEFILE_LIST)))../makefile
    $(call set_default_goal,CASEXPRBASIC)
else
    $(call make_so,CASEXPRBASIC,castlecasexprbasic)
endif
