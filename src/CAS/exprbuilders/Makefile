ifndef root
    include $(dir $(lastword $(MAKEFILE_LIST)))../Makefile
    $(call set_default_goal,CASEXPRBUILDERS)
else
    $(call make_so,CASEXPRBUILDERS,castlecasexprbuilders)
endif
