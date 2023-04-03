#include <stdio.h>
#include "midifile.h"
#include "midifile.c"


void read_midi(char * midifile)
{
  MidiFileEvent_t event;
  unsigned char *data;
  MidiFile_t md = MidiFile_load(midifile);

  event = MidiFile_getFirstEvent(md);

  /* boucle principale */
  while(event)
    {
      // A completer : 
      // affichage du nom des notes
      // affichage de la dur�e des notes

      if (!MidiFileEvent_isVoiceEvent(event)){
        /* ----- */ 
        /* key signature */
        if (MidiFileMetaEvent_getNumber(event) == 0x59){
          int key, mode;
          data = MidiFileMetaEvent_getData(event); 
          key = (int)(data[0]);
          mode = (int)(data[1]); 
          /*
          if (mode == 0) "major"
          else "minor"
          */
        }
      }
      // Tempo
      else  if (MidiFileEvent_isTempoEvent(event)){
        // TODO : get duration of the note.
        int tempo = MidiFileTempoEvent_getTempo(event);
        printf("Tempo : %d\n", tempo);
      }
      else {
          if (MidiFileEvent_isNoteStartEvent(event)){
            /* note start */
            int c = MidiFileNoteStartEvent_getChannel(event);
            int t = MidiFileEvent_getTick(event); // Pitch

            char *note_names[] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
            int note = MidiFileNoteStartEvent_getNote(event);
            int octave = note / 12 - 1;
            int note_name = note % 12;
            printf("%d    %s%d    channel %d\n", t, note_names[note_name], octave, c);
            // Attention channel 10 !!
          }
      }
    
      event = MidiFileEvent_getNextEventInFile(event);
    }
}

void probability_matrix(char *midifile){
    // TODO: 
    // Create a matrix of probabilities for each note to be followed by another note.
    // The matrix will be used to generate new melodies.

    MidiFileEvent_t event;
    unsigned char *data;
    MidiFile_t md = MidiFile_load(midifile);

    event = MidiFile_getFirstEvent(md);

    int matrix[12][12] = {0};

    /* boucle principale */
    while(event){
      if (MidiFileEvent_isNoteStartEvent(event)){
        int note = MidiFileNoteStartEvent_getNote(event) % 12;
        int next_note = MidiFileNoteStartEvent_getNote(MidiFileEvent_getNextEventInFile(event)) % 12;
        matrix[note][next_note] += 1;
      }
      event = MidiFileEvent_getNextEventInFile(event);
    }

    // Display matrix
    for (int i = 0; i < 12; i++){
      for (int j = 0; j < 12; j++){
        printf("%d ", matrix[i][j]);
      }
      printf("\n");
    }
}

void generate_new_midi(int matrix[12][12], int length){
  // Use the probability matrix to generate a new midi file.
  
}


int main (int argc, char *argv[])
{
  printf("Lecture du fichier midi\n");
  // read_midi(argv[1]);
  probability_matrix(argv[1]);
}