/**
 * @file Xml911Recorder.cpp
 * 
 * @ingroup Simulator/Recorders
 *
 * @brief Header file for Xml911Recorder.h
 *
 * The Xml911Recorder provides a mechanism for recording vertex's layout,
 * and compile history information on xml file:
 *     -# vertex's locations, and type map,
 */

#include "Xml911Recorder.h"
#include "Connections911.h"


Xml911Recorder::Xml911Recorder() {

}

Xml911Recorder::~Xml911Recorder() {

}

/// Init radii and rates history matrices with default values
void Xml911Recorder::initDefaultValues() {
    
}

/// Init radii and rates history matrices with current radii and rates
void Xml911Recorder::initValues() {
    
}

/// Get the current radii and rates vlaues
void Xml911Recorder::getValues() {
    
}

/// Compile history information in every epoch
///
/// @param[in] vertices   The entire list of vertices.
void Xml911Recorder::compileHistories(IAllVertices &vertices) {
   
}

/// Writes simulation results to an output destination.
///
/// @param  vertices the Vertex list to search from.
void Xml911Recorder::saveSimData(const IAllVertices &vertices) {
   auto conns = Simulator::getInstance().getModel()->getConnections();
   Connections911 &conns911 = dynamic_cast<Connections911 &>(*conns);

   // create Vertex Types matrix
   VectorMatrix oldTypes(MATRIX_TYPE, MATRIX_INIT, 1, Simulator::getInstance().getTotalVertices(), EXC);
   VectorMatrix vertexTypes(MATRIX_TYPE, MATRIX_INIT, 1, Simulator::getInstance().getTotalVertices(), EXC);
   for (int i = 0; i < Simulator::getInstance().getTotalVertices(); i++) {
      vertexTypes[i] = Simulator::getInstance().getModel()->getLayout()->vertexTypeMap_[i];
      oldTypes[i] = conns911.oldTypeMap_[i];
   }

   // Write XML header information:
   stateOut_ << "<?xml version=\"1.0\" standalone=\"no\"?>\n"
             << "<!-- State output file for the 911 systems modeling-->\n";
   //stateOut << version; TODO: version
   auto layout = Simulator::getInstance().getModel()->getLayout();

   // Write the core state information:
   stateOut_ << "<SimState>\n";
   stateOut_ << "   " << layout->xloc_->toXML("xloc") << endl;
   stateOut_ << "   " << layout->yloc_->toXML("yloc") << endl;
   stateOut_ << "   " << oldTypes.toXML("vertexTypesPreEvent") << endl;
   stateOut_ << "   " << vertexTypes.toXML("vertexTypesPostEvent") << endl;

   // Print out deleted edges and vertices:
   stateOut_ << "   " << conns911.erasedVerticesToXML() << endl;
   stateOut_ << "   " << conns911.changedEdgesToXML(false) << endl;
   stateOut_ << "   " << conns911.changedEdgesToXML(true) << endl;

   // write time between growth cycles
   stateOut_ << "   <Matrix name=\"Tsim\" type=\"complete\" rows=\"1\" columns=\"1\" multiplier=\"1.0\">" << endl;
   stateOut_ << "   " << Simulator::getInstance().getEpochDuration() << endl;
   stateOut_ << "</Matrix>" << endl;

   // write simulation end time
   stateOut_ << "   <Matrix name=\"simulationEndTime\" type=\"complete\" rows=\"1\" columns=\"1\" multiplier=\"1.0\">"
             << endl;
   stateOut_ << "   " << g_simulationStep * Simulator::getInstance().getDeltaT() << endl;
   stateOut_ << "</Matrix>" << endl;
   stateOut_ << "</SimState>" << endl;

}

///  Prints out all parameters to logging file.
///  Registered to OperationManager as Operation::printParameters
void Xml911Recorder::printParameters() {
    
}