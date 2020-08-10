/**

 @file CPUSpikingModel
 @brief Implementation of Model for the spiking neural networks.

 The Model class maintains and manages classes of objects that make up
 essential components of the spiking neural network.
    -# IAllNeurons: A class to define a list of particular type of neurons.
    -# IAllSynapses: A class to define a list of particular type of synapses.
    -# Connections: A class to define connections of the neural network.
    -# Layout: A class to define neurons' layout information in the network.

 The network is composed of 3 superimposed 2-d arrays: neurons, synapses, and
 summation points.

 Synapses in the synapse map are located at the coordinates of the neuron
 from which they receive output.  Each synapse stores a pointer into a
 summation point.

 If, during an advance cycle, a neuron \f$A\f$ at coordinates \f$x,y\f$ fires, every synapse
 which receives output is notified of the spike. Those synapses then hold
 the spike until their delay period is completed.  At a later advance cycle, once the delay
 period has been completed, the synapses apply their PSRs (Post-Synaptic-Response) to
 the summation points.

 Finally, on the next advance cycle, each neuron \f$B\f$ adds the value stored
 in their corresponding summation points to their \f$V_m\f$ and resets the summation points to
 zero.

 The model runs on a single thread.

 */

#include "Connections/Connections.h"
#include "Vertices/IAllNeurons.h"
#include "Edges/IAllSynapses.h"
#include "Layouts/Layout.h"

#pragma once

class CPUSpikingModel : public Model {
public:
   /// Constructor
   CPUSpikingModel();

   /// Destructor
   virtual ~CPUSpikingModel();

   /// Set up model state, if anym for a specific simulation run.
   virtual void setupSim();

   /// Advances network state one simulation step.
   virtual void advance();

   /// Modifies connections between neurons based on current state of the network and behavior
   /// over the past epoch. Should be called once every epoch.
   virtual void updateConnections();

   /// Copy GPU Synapse data to CPU.
   virtual void copyGPUtoCPU();

   /// Copy CPU Synapse data to GPU.
   virtual void copyCPUtoGPU();

};




