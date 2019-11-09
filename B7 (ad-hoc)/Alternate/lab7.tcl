#####################################################
# A simple ad-hoc network with two transmitting nodes
#####################################################

# Declare new Simulator
set ns [new Simulator]

# Open the trace file in write mode
set tf [open out.tr w]
$ns trace-all $tf

# Set name-trace for wireless network
set nf [open out.nam w]
$ns namtrace-all-wireless $nf 200 200

# Set new topography
set topo [new Topography]
$topo load_flatgrid 200 200

# Configure for a wireless node.
$ns node-config -adhocRouting DSDV \
-llType LL \
-macType Mac/802_11 \
-ifqType Queue/DropTail \
-ifqLen 50 \
-phyType Phy/WirelessPhy \
-channelType Channel/WirelessChannel \
-propType Propagation/TwoRayGround \
-antType Antenna/OmniAntenna \
-topoInstance $topo \
-agentTrace ON \
-routerTrace ON \
-macTrace ON 

# Create god object
create-god 3

# Decide the topology
#
#	200					      
#	|					    
#	|					  
#	|					
#	|				  
#	|				
#  100		[n0]             [n1]
#	|	   [tcp0] ......... [sink1]	
#	|	   [ftp0]	
#	|		  
#	|	
#	|
#	|________10______________100_____________200

# Create nodes
set n0 [$ns node]
set n1 [$ns node]

# Set label for nodes (optional)
$n0 label "tcp0"
$n1 label "sink1"

# Locate the nodes on load_flatgrid
$n0 set X_ 10
$n0 set Y_ 100
$n0 set Z_ 0

$n1 set X_ 100
$n1 set Y_ 100
$n1 set Z_ 0

# Define initial state
$ns at 0.0 "$n0 setdest 10 100 15"
$ns at 0.0 "$n1 setdest 100 100 15"

# Declare and attach transport layer protocol
set tcp0 [new Agent/TCP]
$ns attach-agent $n0 $tcp0
set sink1 [new Agent/TCPSink]
$ns attach-agent $n1 $sink1

# Declare and attach application layer protocol
set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0

# connect source to destination
$ns connect $tcp0 $sink1

# start transfer
$ns at 1 "$ftp0 start"

# Define finish procedure
proc finish { } {
    global ns nf tf
    $ns flush-trace
    exec nam out.nam &
    close $tf

    set ctr 0
    set thr 0
    set fid [open out.tr r]
    
    while {[gets $fid line] != -1} {
        if {[string match "r*_1_*AGT*" $line]} {
            set ctr [expr $ctr + 1]
        }
    }
    set thr [expr $ctr/5]
    puts "\nThroughput : $thr"
    exit 0
}

# schedule the events
$ns at 10 "finish"
$ns run

######################## output ###########################
# akshat@pop-os:~/Desktop$ ns lab7.tcl 
#
# num_nodes is set 3
# INITIALIZE THE LIST xListHead
# channel.cc:sendUp - Calc highestAntennaZ_ and distCST_
# highestAntennaZ_ = 1.5,  distCST_ = 550.0
# SORTING LISTS ...DONE!
#
# Throughput : 144
############################################################