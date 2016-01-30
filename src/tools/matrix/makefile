ifndef TOPLEVELWD
    include $(dir $(lastword $(MAKEFILE_LIST)))../makefile
    $(call set_default_goal,MATRIX)
else
    $(call make_so,MATRIX,castlematrix)
endif
