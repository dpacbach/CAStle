ifndef TOPLEVELWD
    include $(dir $(lastword $(MAKEFILE_LIST)))../makefile
    $(call set_default_goal,CASEXPRBUILDERS)
else
    $(call make_so,CASEXPRBUILDERS,castlecasexprbuilders)
endif
