# 5. Simulate the transmission of ping messages over a network topology consisting of 6 nodes and find the number of packets dropped due to congestion.

# Declare new Simulator
set ns [new Simulator]

# Open trace and nam file in write mode
set tf [open out.tr w]
set nf [open out.nam w]
$ns trace-all $tf
$ns namtrace-all $nf

# Decide the topology
#
#       [s0][ping]           [ping][s1]
#          [n0]                [n3]
#            '.                .'	
#              '.            .'
#                '.        .'
#                  '.    .'
#                    [n1]
#                  .'    '.
#                .'        '.
#              .'            '.
#            .'                '.
#          .'                    '.
#        [n2]                     [n4]
#      [ping][d0]               [ping][d1]

# Create the nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]

# set up links
$ns duplex-link $n0 $n1 100Mb 300ms DropTail
$ns duplex-link $n3 $n1 100Mb 300ms DropTail
$ns duplex-link $n2 $n1 1Mb 300ms DropTail
$ns duplex-link $n4 $n1 1Mb 300ms DropTail

# set up queue size
$ns queue-limit $n0 $n1 5
$ns queue-limit $n3 $n1 5
$ns queue-limit $n2 $n1 3
$ns queue-limit $n4 $n1 2

# Declare the agents/protocols
set ping0 [new Agent/Ping]
set ping2 [new Agent/Ping]
set ping3 [new Agent/Ping]
set ping4 [new Agent/Ping]

# Attach the ping with the respective nodes
$ns attach-agent $n0 $ping0
$ns attach-agent $n2 $ping2
$ns attach-agent $n3 $ping3
$ns attach-agent $n4 $ping4

# Connect the ping from source to destination
$ns connect $ping0 $ping2
$ns connect $ping3 $ping4

# Write proc for ping agent
Agent/Ping instproc recv {from rtt} {
	$self instvar node_
	puts "The node [$node_ id] recieved $from with round trip time $rtt"
}

# Write the proc function
proc finish { } {
	global ns nf tf
	$ns flush-trace
	exec nam out.nam &
	close $nf
	close $tf

	set count 0
	set tr [open out.tr r]
	while {[gets $tr line]!=-1} {
        # d is event in the trace file which denotes dropped packets
		if {[string match "d*" $line]} {
			set count [expr $count + 1]
		}
	}
	puts "No. of packet dropped : $count"
	exit 0
}

$ns rtmodel-at 0.9 down $n1 $n4
$ns rtmodel-at 1.9 up $n1 $n4

# schedule events
for {set i 0.1} {$i<2} {set i [expr $i+0.1]} {
    $ns at $i "$ping0 send"
    $ns at $i "$ping3 send"
}

$ns at 5.0 "finish"
$ns run

####################### output #########################
# The node 0 recieved 2 with round trip time 1201.0
# The node 0 recieved 2 with round trip time 1201.0
# The node 0 recieved 2 with round trip time 1201.0
# The node 0 recieved 2 with round trip time 1201.0
# The node 0 recieved 2 with round trip time 1201.0
# The node 0 recieved 2 with round trip time 1201.0
# The node 0 recieved 2 with round trip time 1201.0
# The node 0 recieved 2 with round trip time 1201.0
# The node 0 recieved 2 with round trip time 1201.0
# The node 0 recieved 2 with round trip time 1201.0
# The node 0 recieved 2 with round trip time 1201.0
# The node 0 recieved 2 with round trip time 1201.0
# The node 0 recieved 2 with round trip time 1201.0
# The node 0 recieved 2 with round trip time 1201.0
# The node 0 recieved 2 with round trip time 1201.0
# The node 0 recieved 2 with round trip time 1201.0
# The node 3 recieved 4 with round trip time 1201.0
# The node 0 recieved 2 with round trip time 1201.0
# The node 3 recieved 4 with round trip time 1201.0
# The node 0 recieved 2 with round trip time 1201.0
# The node 3 recieved 4 with round trip time 1201.0
# The node 0 recieved 2 with round trip time 1201.0
# The node 3 recieved 4 with round trip time 1201.0
# No. of packet dropped : 5
########################################################
