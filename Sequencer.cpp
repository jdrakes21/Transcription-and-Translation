/*****************************************
** File:    Sequencer.cpp
** Project: CMSC 202 Project 3, Spring 2023
** Author:  Jervon Drakes
** Date:    3/31/23
** Section: 44
** E-mail:  jdrakes1@umbc.edu
**
** This file contains the Sequencer.cpp file for Project 3.
** This program reads the Sequencer.h file and its functions and
** executes those functions to implement proj3.cpp
**
**
**
***********************************************/

#include "Sequencer.h"

// Sequencer(constructor)
// creates a new sequencer to hold one or more DNA/mRNA strands make of multiples of three nucleotides
Sequencer::Sequencer(string fileName){
  
  m_fileName = fileName;
  
}

// Sequencer(destructor)
// Deallocates all dynamic aspects of a Sequencer
Sequencer::~Sequencer(){

  
  // deallocates the memory within the m_DNA vector
  for(unsigned int i = 0; i < m_DNA.size(); i++){ 

    delete m_DNA[i];
  }

  // deallocates the memory within the m_mRNA vector
  for(unsigned int i = 0; i < m_mRNA.size(); i++){
    delete m_mRNA[i];
    
  }
}

// StartSequencing
// Calls ReadFile and continually calls MainMenu until the user exits
void Sequencer::StartSequencing(){
  ReadFile();
  MainMenu();
}

//DisplayStrands
// Displays each strand in both mDNA and mRNA
void Sequencer::DisplayStrands(){


  int dnanumber = 1; // the dna number of the strands loaded from a file

  // loops through the m_DNA vector to display the strands within it
  for(unsigned int i = 0; i < m_DNA.size(); i++){
    
    cout << "DNA" <<  " " << dnanumber << endl;
    cout << *m_DNA.at(i)  << endl;
    dnanumber++;
    
  }
  
  int mrnanumber = 1; // the mrna number of the strands loaded from a file

  // loops through the m_mRNA vector to display the starnds within it
  for(unsigned int i = 0; i < m_mRNA.size(); i++){
   
    cout << "mRNA" << " " << mrnanumber << endl;
    cout << *m_mRNA.at(i) << endl;
    mrnanumber++;
  }
    
}

// ReadFile
// Reads in a file of DNA strands
void Sequencer::ReadFile(){

  ifstream inputStream;

  // opens the respective file 
  inputStream.open(m_fileName);
 
  
  
  string name; // name assigned to the specific dna strand
  string dnaSequence; // the sequence of the dna strand

    // loops through the file and retrives the name and dna sequence 
  while(getline(inputStream, name, ',') && getline(inputStream, dnaSequence, '\n')){
    Strand* userStrand = new Strand(name);
    
     // loops through the dna sequence to retrive the characters within that sequence
     for(unsigned int i = 0; i < dnaSequence.length(); i++){
       // inserts the charcaters into the userStrand object
       if(dnaSequence[i] != ',' && dnaSequence[i] != '\n' && dnaSequence[i] != ' '){	 	
	 userStrand->InsertEnd(dnaSequence[i]);
	 
       }
       
     }
     // adds the contents of userStrand to the m_DNA vector
   m_DNA.push_back(userStrand);
   
  }
  
  inputStream.close();
}

// MainMenu
// Displats the main menu and manages exiting
int Sequencer::MainMenu(){
  int choice = 0;
  
  cout <<"Opened File"<< endl;

  cout << m_DNA.size() <<  " " << "strands loaded" << endl;

  // the menu is printed once the user's choice is not 5
  while(choice != 5){
    // the menu is printed repeatedly once the conditions are met
    do{
      cout << "What would you like to do?" << endl;
      cout << "1. Display Strands " << endl;
      cout << "2. Reverse Strands " << endl;
      cout << "3. Transcribe DNA to mRna " << endl;
      cout << "4. Translate mRNA to Amino Acids " << endl;
      cout << "5. Exit " << endl;
      cin >> choice;
    }while(choice > 5 || choice < 1);

    switch(choice){
    case 1:
      // the strands are displayed 
      DisplayStrands();
      break;
    case 2:
      // the user is asked to reverse either a dna sequence or mrna sequence
      ReverseSequence();
      break;
    case 3:
      // dna strands are trasncribed to mrna stranes
      Transcribe();
      break;
    case 4:
      // mrna strands are translated to amino acids
      Translate();
      break;
    case 5:
      // the progrm terminates printing the below
      cout << "Exiting program" << endl;
      cout << "Deleting DNA strands" << endl;
      cout << "Deleting mRNA strands" << endl;
    }
  }
  return choice;
}

// ChooseDNA
// Asks the user to choose one strand to use from loaded DNA strands
int Sequencer::ChooseDNA(){
  
  
  int dnaSize;
  dnaSize = (int) m_DNA.size();

  int strandChoice;

  // condition which determined if the size of the dna vector is 1 or not
  if(dnaSize != 1){

    // asks the user which strand they wish to choose and repeatedly once the conditions for the choice is met
    do{
      cout << "Which Strand to work with?" << endl;
      cout << "Choose 1 - " << m_DNA.size() << endl;
      cin >> strandChoice;
      
    }while(strandChoice < 1 || strandChoice > dnaSize);

    
  }else{
    // once the size of the dna vector is 1 the strandChoice is 1
    strandChoice = 1;
  }
  
  return strandChoice;
}

// ChooseMRNA
// Asks the user to choose one strand from transcribed mRNA strands
int Sequencer::ChooseMRNA(){

  
  int mrnaSize;
  mrnaSize = (int) m_mRNA.size(); // size of mrna vector
  
  int chosenStrand;

  // condition which determines if the size of the mrna vector is one or not
  if(mrnaSize != 1){

    // condition which determines if the size of the mrna vector is 0 or not 
    if(mrnaSize != 0){

      // asks the user which strand they wish to choose and repetedly if the condtions for the choice is  met
      do{
	cout << "Which Strand to work with?" << endl;
        cout << "Choose 1 - " << mrnaSize << endl;
        cin >> chosenStrand;
	
      }while(chosenStrand < 1 || chosenStrand > mrnaSize);

      // if the mrna vector size is 0 then the chosenStrand is 0  
    }else{
     chosenStrand = 0;
   }

    // if the mrna vector size is 1 then the choseStrand is 1  
  }else{
    chosenStrand = 1;
  }
  return chosenStrand;  
}
	       
// ReverseSequence
// User chooses to reverse either a DNA strand or mRNA strand
void Sequencer::ReverseSequence(){

  
  int uChoice;
  int sequencerChoice;
  const int mrnaChoice = 2;

  // asks the user which strand to reverse and repeatedly if the conditions for the sequencer choice are met
  do{
    
    cout << "Which type of strand to reverse?" << endl;
    cout << "1. DNA" << endl;
    cout << "2. mRNA" << endl;
    cin >> sequencerChoice;
    
  }while(sequencerChoice < 1 || sequencerChoice > mrnaChoice);

  // condition to determine if the sequencer choice is 1
  if(sequencerChoice == 1){

    // ChooseDNA function is called and assigned to uChoice
    uChoice = ChooseDNA();

    //the choice is indexed and the specific strand within the dna vector is reversed 
    m_DNA[uChoice - 1]->ReverseSequence();
    
    cout << "Done reversing DNA" << " " << uChoice << "'s" << " " << "strand" << endl;

    // condition to determine if the sequencer choice is 2
  }else if(sequencerChoice == 2){

    // ChooseMRNA function is called and assigned to uChoice
    uChoice = ChooseMRNA();

    // condition to determine if uChoice is 0
    if(uChoice == 0){
      
      // the following is outputted if that condition is met
      cout << "No mRNA to reverse; transcribe first" << endl;
      
    }else{

      //otherwise the selected strand of mrna is reversed
      m_mRNA[uChoice - 1]->ReverseSequence();

      cout << "Done reversing mRNA" << " " << uChoice << "'s" << " " << "strand" << endl;

    }
  }
}

// Transcribe
// Iterates through each DNA strand in m_DNA to translate to m_RNA
void Sequencer::Transcribe(){

  
  int dnaSize;
  dnaSize = (int) m_DNA.size();

  char mrnaProtein; 
  char mrnaSequence;

  for(int i = 0; i < dnaSize; i++){

    
    Strand* dnaSequence = m_DNA[i]; // creates a new object of strand for the dna vector
    
    Strand* usermRna = new Strand(dnaSequence->GetName()); // creates another object of strand which retrives the name for each dnaSequence
    
      
    for(int j = 0; j < dnaSequence->GetSize(); j++){

      mrnaProtein = dnaSequence->GetData(j); // retrives the sequences for each strand

      //conditional to determine if mrnaProtein is A
      if(mrnaProtein == 'A'){
	// once met the mrnaSequence is assigned a value of U
	mrnaSequence = 'U';

	// conditional to determine if mrnaProtein is T
      }else if(mrnaProtein == 'T'){
	// once met the mrnaSequebce is assigned a value A
	mrnaSequence = 'A';

	// conditional to determine if mrnaProtein is C
      }else if(mrnaProtein == 'C'){
	// once met the mrnaSequence is assigned a value G
	mrnaSequence = 'G';

	// conditional to determine if mrnaProtein is G 
      }else if(mrnaProtein == 'G'){
	// once met the mrnaSequence is assigned a value of C
	mrnaSequence = 'C';
       
      }
      // the mrnaSequence is inserted into usermRna
      usermRna->InsertEnd(mrnaSequence);
      }
    
    // usermRna is then added to the m_mRna vector
     m_mRNA.push_back(usermRna);

    }
     
  cout << dnaSize << " " << "strands of DNA successfully transcribed into new mRNA strands" << endl;
  
}

// Translate
// Iterates through a chose mRNA strand and converts to amino acids
void Sequencer::Translate(){
  
  
  int userChoice;

  const int trinucleotideNum = 3;
  
  userChoice = ChooseMRNA(); // calls the ChooseMRNA function and assigns its value to userChoice

  // conditional to determine if userChoice is 0
  if(userChoice == 0){

    // the program outputs this once condition is met
    cout << "No mRNA to translate; transcribe first" << endl;

    
  }else{
    
  string aminoAcid;

  
  Strand* mrnaStrand = m_mRNA[userChoice - 1];// new object of Strand is created

  cout << "***" << mrnaStrand->GetName() << "***" << endl;

  // loops through mrnaStrand and retirves charcaters by 3's
  for(int j = 0; j < mrnaStrand->GetSize(); j += trinucleotideNum){

    string trinucleotide = "";

    // conditional to get the characters of a sequence for a specific strand
    if((mrnaStrand->GetSize() - j) >= 3){

      trinucleotide += mrnaStrand->GetData(j); // assigns trinucleotide the first charcater
      trinucleotide += mrnaStrand->GetData(j+1); // assigns trinucleotide the second character
      trinucleotide += mrnaStrand->GetData(j+2); // assigns trinucleotide the third character
     
      aminoAcid = Convert(trinucleotide); // calls the convert function which assists with the translation of mrna strands to amino acids
       
      cout << trinucleotide << "->" << aminoAcid << endl;
      trinucleotide = "";
	
  
    }
  }
  cout << "Done translating mRNA" << " " << userChoice << "'s stran\
d"
 << endl;

  
  }
}

// Convert
// Converts codon(three nodes) into an amino acid
string Sequencer::Convert(const string trinucleotide){

  // conditional to determine if trinucleotide is any of these characters
  if((trinucleotide=="AUU")||(trinucleotide=="AUC")||(trinucleotide=="AUA"))

    // once met Isoleucine is returned
    return ("Isoleucine");

  // conditional to determine if trinucleotide is any of these characters
  else if((trinucleotide=="CUU")||(trinucleotide=="CUC")||(trinucleotide=="CUA"\
)||
          (trinucleotide=="CUG")|| (trinucleotide=="UUA")||(trinucleotide=="UUG\
"))
    // once met Leucine is returned
    return ("Leucine");

  // conditional to determine if trinucleotide is any of these charcaters
  else if((trinucleotide=="GUU")||(trinucleotide=="GUC")||
          (trinucleotide=="GUA")||(trinucleotide=="GUG"))

    // once met Valine is returned
    return ("Valine");

  // conditional to determine if trinucleotide is any of these charcaters
  else if((trinucleotide=="UUU")||(trinucleotide=="UUC"))

    // once met Phenylalanine is returned
    return ("Phenylalanine");

  // conditional to determine if trinucleotide is these collection of characters
  else if((trinucleotide=="AUG"))

    // once met Methionine (START) is returned
    return ("Methionine (START)");

  // conditional to determine if trinucleotide is any of these collection of characters
  else if((trinucleotide=="UGU")||(trinucleotide=="UGC"))

    // once met Cysteine is returned
    return ("Cysteine");

  // conditional to determine if trinucleotide is any of these collection of characters
  else if((trinucleotide=="GCU")||(trinucleotide=="GCC")||
          (trinucleotide=="GCA")||(trinucleotide=="GCG"))

    // once met Alanine is returned
    return ("Alanine");

  // conditional to determine if trinucleotide is any of these collection of charcaters
  else if((trinucleotide=="GGU")||(trinucleotide=="GGC")||
          (trinucleotide=="GGA")||(trinucleotide=="GGG"))

    // once met Glycine is returned
    return ("Glycine");

  // conditional to determine if trinucleotide is any of these collection of charcaters
  else if((trinucleotide=="CCU")||(trinucleotide=="CCC")||
          (trinucleotide=="CCA")||(trinucleotide=="CCG"))

    // once met Proline is returned
    return ("Proline");

  // conditional to determine if trinucleotide is any of these collection of characters
  else if((trinucleotide=="ACU")||(trinucleotide=="ACC")||
	  (trinucleotide=="ACA")||(trinucleotide=="ACG"))

    // once met Threonine is returned
    return ("Threonine");

  // conditional to determine if trinucleotide is any of thess collection of characters
  else if((trinucleotide=="UCU")||(trinucleotide=="UCC")||
          (trinucleotide=="UCA")||(trinucleotide=="UCG")||
          (trinucleotide=="AGU")||(trinucleotide=="AGC"))
    
    // once met Serine is returned
    return ("Serine");

    // conditional to determine if trinucleotide is any of these collection of characters
  else if((trinucleotide=="UAU")||(trinucleotide=="UAC"))
    
    // once met Tyrosine is returned
    return ("Tyrosine");

    // conditional to determine if trinucleotide is any of these collection of charcaters
  else if((trinucleotide=="UGG"))
    
    // once met Tryptophan is returned
    return ("Tryptophan");

    // conditional to determine if trinucleotide is any of these collection of characters
  else if((trinucleotide=="CAA")||(trinucleotide=="CAG"))

    // once met Glutamine is returned
    return ("Glutamine");

    // conditional to determine if trinucleotide is any of these colection of characters
  else if((trinucleotide=="AAU")||(trinucleotide=="AAC"))

    // once met Asparagine is returned
    return ("Asparagine");

  // conditional to determine if trinucleotide is any of these collection of characters
  else if((trinucleotide=="CAU")||(trinucleotide=="CAC"))

    // once met Histidine is returned
    return ("Histidine");

  // conditional to determine if trinucleotide is any of these collection of characters
  else if((trinucleotide=="GAA")||(trinucleotide=="GAG"))

    // once met Glutamic acid is returned
    return ("Glutamic acid");

  // conditional to determine if trinucleotide is any of these collection of characters
  else if((trinucleotide=="GAU")||(trinucleotide=="GAC"))

    // once met Aspartic acid is returned
    return ("Aspartic acid");

  // conditional to determine if trinucleotide is any of these collection of characters
  else if((trinucleotide=="AAA")||(trinucleotide=="AAG"))

    // once met Lysine is returned
    return ("Lysine");

  // conditional to determine if trinucleotide is any of these collection of characters
  else if((trinucleotide=="CGU")||(trinucleotide=="CGC")||(trinucleotide=="CGA"	\
)||(trinucleotide=="CGG")||(trinucleotide=="AGA")||(trinucleotide=="AGG"\
))
    // once met Argine is returned 
    return ("Arginine");

  // conditional to determine if trinucleotide is any of these collection of characters
  else if((trinucleotide=="UAA")||(trinucleotide=="UAG")||(trinucleotide=="UGA"\
))
    // once met Stop is returned
    return ("Stop");
  
  else
    cout << "returning unknown" << endl;
  return ("Unknown");
}
