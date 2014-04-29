#ifndef FLTEXTBLOCK_H
#define FLTEXTBLOCK_H

#include "FLSuggestionsContainer.h"
#include "FLRequestDataHolder.h"
#include "FLTextBlock.h"
#include "PatternRecognizer/Platform.h"
#include "FleksyListenerInterface.h"
#include "FLKeyboard.h"
#include "FLUnicodeString.h"

class SystemsIntegrator;
class FLTypingController;

class FLTextBlock{
public:
	FLTextBlock(FleksyListenerInterface &listener);
  ~FLTextBlock();
  
  //Getters/Setters
  FLSuggestionsContainer *getResponse();
  void setCorrectedText(const FLUnicodeString &text);
  FLUnicodeString getCorrectedText();
  void setTextEntered(const FLUnicodeString &text);
  FLUnicodeString getTextEntered() const;
  int getLength() const;
  bool isPunctuationInside() const;
	void setIsPunctuationInside(bool isPunctuation);
  bool isSpaceEnabled() const;
  void setIsSpaceEnabled(bool isSpaceEnabled);
  bool isNewLineTextBlock() const;
  bool isSymbolsTextBlock() const;
  void setIsSymbolsTextBlock(bool symbol);
  bool isEmojiTextBlock() const;
  void setIsEmojiTextBlock(bool isEmoji);
  bool isEndSentence() const;
  bool isBeginSentence() const;
  bool isUserEditedText() const;
  void setIsAccuratelyTyped(bool isAccuratelyTyped);
  bool getIsAccuratelyTyped() const;
  bool isVirgin() const; // True if this text block contains no text or spaces.
  
	FLRequestDataHolder *getRequest();
  FLUnicodeString getText() const;
  int getSuggestionIndex() const;
  int getSuggestionIndex_dataexplorer() const;
  
  void setSuggestionIndex(int suggIndex);
	bool getIsExactEntry() const;
  bool isCorrected() const;
  
  void addCharacter(FLPoint p, const FLUnicodeString &c, int index, FLKeyboardPtr &keyboard);
  void setSuggestions(const std::vector<FLUnicodeString>& suggestions);
  void setRequestPoints(const std::vector<FLPoint> &points);
	
	void deleteText();
  FLUnicodeString deleteCharacter(int indx, FLTypingController *tc, int oldLength, int oldIndx,  int userCursorPos);
  void createNewLineCharacter();
  void cleanTextBlock();
  void resetSuggestionIndex();
  void correctEnteredText(bool isSpaceAfter);
  void correctTextOnVSwipe();
  void nextSuggestion();
	void prevSuggestion();
  FLUnicodeString getTextToCorrect();
  
  FLUnicodeString displayString(int tbNumber = -1, bool withPoints = false);
  void printSelf(int tbNumber = -1, bool withPoints = false);
  void printfSelf(int tbNumber = -1, bool withPoints = false);
  FLUnicodeString getTextBlockInfo(int tbNumber);
  FLUnicodeString toLowerCase(const FLUnicodeString &string);
  
  bool containsNonAlphaCharacters(SystemsIntegrator* fleksy) const;
  bool containsApostrophe() const;
  bool isSplitWithSpace() const;
  void setUserCapitalization(bool isUserSet);
  bool userSetCapitalization() const;
  bool replacedSuggestion() const;
  
  int getLengthBeforePreviousUpdate() const;
  int getLengthDiff() const;
  
  // Functions for debug.
  void rememberContext(const std::vector<FLUnicodeString> &tokens) { context = tokens; }
  std::vector<FLUnicodeString> getContext() const { return context; }
  
private:
  FleksyListenerInterface &out;
	FLSuggestionsContainer *response;
	FLRequestDataHolder *request;
	int suggestionIndx;
	FLUnicodeString correctedText;
	bool isPunctuation;
  bool isSpaceAfterTextBlock;
  bool isExactEntry; // if typed the word accuratly
  bool isSymbolTextBlock;
  bool addedWordToDictionary;
  bool isUserSetCapitalization;
  bool userEditedText;
  bool changedToNextSuggestion;
  bool isAccuratelyTyped;
  bool isEmoji;
  
  void changeSuggestion(int offset);
  FLUnicodeString matchCase(const FLUnicodeString &word);
  void prepareTextBlockToRecieveOrRemoveCharacters();
  
  void printTextBlock() const;
  void deleteSuggestions();
  
  
  int lengthBeforePreviousUpdate = 0;
  void setLengthBeforePreviousUpdate(int length);
  
  // Data For debug.
  std::vector<FLUnicodeString> context;
};

#endif
