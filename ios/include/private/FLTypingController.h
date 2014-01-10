#ifndef FLTYPINGCONTROLLER_H
#define FLTYPINGCONTROLLER_H

#include <vector>
#include <string>
#include <map>
#include "FLTouchPoint.h"
#include "FLTextBlock.h"
#include "FLRequestDataHolder.h"
#include "PatternRecognizer/Platform.h"
#include "FleksyListenerInterface.h"
#include "FLTextBlockCursor.h"
#include "SystemsIntegrator.h"
#include "FLConsistencyChecker.h"
#include "FLTrackEvents.h"
#include "FLDataCollector.h"
#include "FLUnicodeString.h"
#include "FLAutoLearn.h"

class FLConsistencyChecker;

struct CursorChangeEvent{
  bool useThisEvent = false;
  int newSelStart = 0;
  int newSelEnd = 0;
};

class FLTypingController{
  
public:
	FLTypingController(FleksyListenerInterface &listener, SystemsIntegrator* fleksy);
  ~FLTypingController();
  
  //FleksyAPI calls
  void sendPoint(float x, float y, long long time, int offset, FLUnicodeString character);
  void backAndForthSwipe(float length = 0);
	void swipeRight(const FLUnicodeString& hint, float length = 0);
	void swipeLeft(float length = 0);
	void swipeUp(float length = 0);
	void swipeDown(float length = 0);
  void enterSwipe(float length = 0);
  void shiftPressed(const std::string &who, bool userPress = false);
  void setActiveKeyboard(FLKeyboardID id, bool buttonPress);
  FLKeyboardID getActiveKeyboardID();
  void setCorrectionMode(FLCorrectionMode mode);
  FLCorrectionMode getCorrectionMode();
  void cursorSelectionChanged(int selectionStart, int selectionEnd);
  void startTypingSession(bool platformMovesCursor = false);
  void endTypingSession();
  void postLoadSetup();
  void setCapitalizationMode(FLCapitalizationMode mode);
  FLCapitalizationMode getCapitalizationMode();
  void setVoiceFeedback(bool isOn);
  void setDeleteMode(FLDeleteMode mode);
  void setFieldAction(FLFieldAction fieldAction);
  void setPunctuationSpaceMode(FLPunctuationSpaceMode mode);
  void setTextFieldType(FLTextFieldType type);
  void longPress(FLLongPressType type, float x, float y);
  bool isShifted();
  FLFieldAction getCurrentFieldAction();
  
  void setMaxNumberOfSuggestions(int numOfSuggestions); //Private API uses this
  FLUnicodeString getVersionNumber(); //Version number of TC
  
  
  //Here for testing
  void sendCharacter(const FLUnicodeString &c);//Testing sends character and this function coverts it into points and calls sendPoint()
  int getCursorPosition();//only used by TC tester
  FLUnicodeString getTextFromTextBlocks();// in public for debugging
  bool getShiftState();//only used by TC tester
  //EOF testing functions

  //Crazy Cheker uses these
  FLTextBlockCursor * getTextBlockCursor();
  void setUserCursor(int userCursor, const std::string &caller);
  void resetIgnoreNextCursorUpdateCount();
  void underlineCurrentTextBlock();
  void parseExistingText(const FLUnicodeString &existingText = FLUnicodeString((const unsigned char *)""), int cursorPosition = -1, bool deletedSelectedText = false);
  //EOF crazyChecker functions
  
  void setCurrentKeyboardLayout(const std::string &keyboardLayout);
  FLDataCollector *getDataCollector();
  
  void biasPointForChar(FLPoint& p1, int offset);

private:
  std::string lastBatchEditBeginFunction; // Debugging?

	FleksyListenerInterface &out;
	std::vector<FLUnicodeString> punctuation;
  std::vector<FLUnicodeString> specialCases;
  std::vector<FLUnicodeString> emoticons;
	std::vector<FLTextBlock*> textBlocks;
  std::vector<FLUnicodeString> last3events;
  
  FLUnicodeString versionNumber;
	int expectedUserCursor;//loaction of the cursor
  int userSelectionStart;
  int userSelectionEnd;
  
  int gameKeyChargingOffset;
  
	int ignoreNextCursorUpdateCount;//how may cursor updates to ignore(by how much cursor has moved)
  double lastCursorUpdateMatched;
  
  int maxNumberOfSuggestions;
  bool isShiftPressed;
  bool simulateSystemCursorUpdates; //true = simulation of updates, false - updates come from the system
  bool isUserSelectedTB; //indicates if user selectedTB by moving the cursor
  FLCorrectionMode correctionMode;
  
  //TODO:rename this 
  bool isFirstInputAfterParsing;
  //////
  bool isUserShifting;
  bool isEngineLoaded;
  bool voiceFeedback;
  bool startedTypingSession;
  bool inBatchEdit;

  CursorChangeEvent cursorChangeEvent;
  
  FLCapitalizationMode capitalizationMode;
  FLDeleteMode deleteMode;
  FLFieldAction fieldAction;
  FLPunctuationSpaceMode punctuationSpaceMode;
  FLTextFieldType textFieldType;
  FLLongPressType longPressType;
  FLMessageType spaceBarState;
  
  FLUnicodeString lastDeletedRawText;
  FLUnicodeString lastDeletedCorrectedWord;
  
  FLUnicodeString gameText;
  double lastTapTime;
  
  //Created in TC, so TC needs to destroy these
  FLTextBlockCursor *tbCursor = NULL;
  FLConsistencyChecker *crazyCheck = NULL;
  FLDataCollector *dataCollector = NULL;
  //Just pointers
  SystemsIntegrator *fleksy = NULL;
  FLTextBlock *lastUpdatedTB = NULL;
  //FLAutoLearn *autoLearner = NULL;
  
  //Debug stuff
  void printTextBlocks();
  FLUnicodeString getSlashSeparatedSuggestions(const std::vector<FLUnicodeString> &suggestions);
  
  //Game key charging
  FLUnicodeString getIntendedCharacter(int offset);
  
  //Stuff that deletes
  void backspace(float length);
  void deleteTextBlock();
  void deleteCharacterAt(int indx);
  void deleteCurrentTextBlock();
  int deleteAnySelectedText(FLExternalEditorState &state, bool isDeleting = false);
  
  //TextBlock correction operations
  std::vector<FLUnicodeString> getTwoPreviousTokens(int textBlockIndex);
  void getSuggestionsForTextBlock(FLTextBlock *tb, int textBlockIndex = -1);
  void handleVerticalSwipe(bool isUp);
  void correctTextBlockOnSwipeRight(FLTextBlock *tb);
  void correctTextBlockOnVerticalSwipe();
  void correctToNextSuggestion(FLTextBlock *tb, bool isUp);
  void changeTextBlockSuggestionWithCursorInTheMiddle(FLTextBlock *currTextBlock, int indxInTextBlock, bool isUp);
  bool checkForRepeatedTypingAndLearn(FLTextBlock *tb);
  void createEmoticonTextBlock();
  
  //Various helper functioins
  FLUnicodeString getNearestChar(FLPoint p);
  std::vector<FLPoint> getPointsForText(const FLUnicodeString &word);
  void reset();
  void GCtextBlocks();

  void populateSpecialVectors();

  void ignoreNextCursorUpdate(const std::string &from, int num_ignores);
  void expectCursorUpdates(const std::string &from, int numOfUpdates);

  void onBeginBatchEdit();
  void onEndBatchEdit();
  void batchEditCheck(int newSelStart, int newSelEnd);

  void handleNonQWERTYCharacter(const FLUnicodeString &Character, FLPoint p);
  FLUnicodeString toLowerCase(const FLUnicodeString &word);

  bool selectedTextAndConsistencyCheck(bool isVerticalSwipe = false, bool isDeleting = false);
  void addRemoveFromDictionary(FLTextBlock *tb);
  void updateTBCursorAfterParsing(FLUnicodeString &blockText, FLExternalEditorState state);
  void getReadyForInput();
  void closeComposingRegionAt(int position);
  double getUpdateTimeDiff();
  void recordLastEvent(const FLUnicodeString &event);
  FLUnicodeString getGameCharacter(int index);
  std::vector<FLPoint> getSubVector(const std::vector<FLPoint> &original, int start, int end);
  void resetLongPressType();
  int getNumberOfQuotes();
  
  void apostropheSmergeCheck();

  bool canEatSpace(const FLUnicodeString &c);
  bool canAddSpace(const FLUnicodeString &c, FLTextBlock *prevTB);
  bool canAddSpaceAfterEating(const FLUnicodeString &c);
  bool canAddSymbolToTextBlock(const FLUnicodeString &character, const FLUnicodeString &blockText);

  bool isSymbolAllowedToCorrect(const FLUnicodeString &character);

  bool isInPunctuation(const FLUnicodeString &symbol);

  int calculateEndOfTextBlock(FLTextBlock *tb);
  void setLastDeletedWord(FLTextBlock *tb);

  
  //User cursor operations
  void moveCursorToPosition(int position);
  int setSpaceFlagOnTextBlock(FLTextBlock * tb, bool isSpaceEnabled);
  void accountForLenghthDiffWhenCorrectingWords(int lengthDiff);
  void changeUserCursor(int byNumber, const std::string &caller);
  void incrementUserCursorBy(int number, const std::string &caller);
  void decrementUserCursorBy(int number, const std::string &caller);
  int getUserCursorPos();
  void setUserSelection(int selectionStart, int selectionEnd);
  void onUpdateSelection(int oldSelStart, int oldSelEnd, int newSelStart, int newSelEnd);
  
  //TextBlock operations
	int addTextBlock(FLTextBlock *block);
  FLTextBlock* createTextBlockFromExistingText(FLUnicodeString &blockText);
	void addSymbolsTextBlock(bool keepSpaceOnCurrTB);
  void createTextBlockFromExistingTextAndUpdateTBCursor(FLUnicodeString &blockText);
  void updateTextBlockCursorBasedOnCursorPosition(int cursorPosition = -1);
  void splitTextBlockWithSpace(FLTextBlock *TBtoSplit, int indxInTBtoSplitAt, int indxOfTBinVector);
  void mergeTextBlocks(FLTextBlock *tb1, FLTextBlock *tb2, int tb1Indx, int indxInTB);
  void mergeTextBlocksCheck();
  void checkTextBlockForSplittage(int indexOfTB);
  
  //UI&User Feedback
  void setComposingRegionForTextBlock(FLTextBlock* tb, int userCursor, bool isSpaceIncluded);
  void updateShiftState(bool forcedUpdate = false);
  void updateCandidatesView(FLTextBlock *tbToUpdate = NULL);
  void clearCandidatesView();
  void forceCandidateViewUpdate(FLTextBlock *tbToUpdate = NULL);
  void speak(FLUnicodeString text, bool isDeleted);
  void speak(FLTextBlock *tb, bool isDeleted, bool forceSpeak = false);
  FLMessageType getSpaceBarState();
  void sendSpacebarState(bool forceSend = false);
};

#endif
