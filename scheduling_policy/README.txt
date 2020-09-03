
how to compile:
	type (make)
	the makefile will create executable file (set_policy)

how to run:
	run (set_policy) with 2 parameters(schedule_policy_number , priority_number)
	by typing: sudo ./set_policy <SCHED_NUMBER> <priority> 
	   

example:
	sudo ./set_policy 2 19 
	
explanation:
	schedule policy changed to SCHED_RR
	and the process priority changed to 19
	
	(2 is defined as SCHED_RR policy)
	
note:
	some of the schedule policies required only (priority = 0)




	 
