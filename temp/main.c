#include <android/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <linux/limits.h>
#include <sys/sendfile.h>
#include <sys/stat.h>

#include "../beatsaber-hook/shared/inline-hook/inlineHook.h"
#include "../beatsaber-hook/shared/utils/utils.h"
typedef struct __attribute__((__packed__)) {
	void* _levelID;
	void* _songName;
	void* _songSubName;
	void* _songAuthorName;
	void* _levelAuthorName;
	void* _audioClip;
	float _beatsPerMinute;
	float _songTimeOffset;
	float _shuffle;
	float _shufflePeriod;
	float _previewStartTime;
	float _previewDuration;
	void* _coverImageTexture2D;
	void* _environmentSceneInfo;
	void* _difficultyBeatmapSets;
	void* _beatmapCharacteristics;
	void* _beatmapLevelData;
	void* _getBeatmapLevelDataResult;
	void* _audioClipPtr;
	void* _coverImageTexture2DPtr;
	void* _environmentSceneInfoPtr;
} BeatmapLevelSO;
typedef struct __attribute__((__packed__)) {
	void* _tableView;
	void* _cellPrefab;
	void* _cellReuseIdentifier;
	float _cellWidth;
	void* _additionalContentModel;
	void* _promoPackIDStrings;
	void* didSelectPackEvent;
	void* _promoPackIDs;
	void* _levelPackCollection;
	char _isInitialized;
	int _selectedColumn;
	void* _tableViewPtr;
	void* _cellPrefabPtr;
	void* _additionalContentModelPtr;
} LevelPacksTableView;
typedef struct __attribute__((__packed__)) {
	void* _bgImage;
	void* _normalTextColor;
	void* _selectedTextColor;
	void* _highlightTextColor;
	void* _selectedHighlightTextColor;
	void* _normalBGColor;
	void* _selectedBGColor;
	void* _highlightBGColor;
	void* _selectedHighlightBGColor;
	void* _bgImagePtr;
} TextSegmentedControlCellNew;
typedef struct __attribute__((__packed__)) {
	void* _onText;
	void* _offText;
	void* _onTextColor;
	void* _offTextColor;
	void* _highlightColor;
	void* _selectedColor;
	void* _toggleWasPressedSignal;
	void* _offImage;
	void* _onImage;
	void* _offTextUI;
	void* _onTextUI;
	void* didSwitchEvent;
	char _isOn;
	char _isHighlighted;
	void* _toggleWasPressedSignalPtr;
	void* _offImagePtr;
	void* _onImagePtr;
	void* _offTextUIPtr;
	void* _onTextUIPtr;
} Toggle;
MAKE_HOOK(BeatmapLevelSO_get_levelID, 0x129C154, void, BeatmapLevelSO self) {
	log("Called BeatmapLevelSO_get_levelID Hook!");
	return BeatmapLevelSO_get_levelID(self);
}

MAKE_HOOK(BeatmapLevelSO_get_songName, 0x12B132C, void, BeatmapLevelSO self) {
	log("Called BeatmapLevelSO_get_songName Hook!");
	return BeatmapLevelSO_get_songName(self);
}

MAKE_HOOK(BeatmapLevelSO_get_songSubName, 0x12B1334, void, BeatmapLevelSO self) {
	log("Called BeatmapLevelSO_get_songSubName Hook!");
	return BeatmapLevelSO_get_songSubName(self);
}

MAKE_HOOK(BeatmapLevelSO_get_songAuthorName, 0x12B133C, void, BeatmapLevelSO self) {
	log("Called BeatmapLevelSO_get_songAuthorName Hook!");
	return BeatmapLevelSO_get_songAuthorName(self);
}

MAKE_HOOK(BeatmapLevelSO_get_levelAuthorName, 0x12B1344, void, BeatmapLevelSO self) {
	log("Called BeatmapLevelSO_get_levelAuthorName Hook!");
	return BeatmapLevelSO_get_levelAuthorName(self);
}

MAKE_HOOK(BeatmapLevelSO_get_beatsPerMinute, 0x12B134C, float, BeatmapLevelSO self) {
	log("Called BeatmapLevelSO_get_beatsPerMinute Hook!");
	return BeatmapLevelSO_get_beatsPerMinute(self);
}

MAKE_HOOK(BeatmapLevelSO_get_songTimeOffset, 0x12B1354, float, BeatmapLevelSO self) {
	log("Called BeatmapLevelSO_get_songTimeOffset Hook!");
	return BeatmapLevelSO_get_songTimeOffset(self);
}

MAKE_HOOK(BeatmapLevelSO_get_shuffle, 0x12B135C, float, BeatmapLevelSO self) {
	log("Called BeatmapLevelSO_get_shuffle Hook!");
	return BeatmapLevelSO_get_shuffle(self);
}

MAKE_HOOK(BeatmapLevelSO_get_shufflePeriod, 0x12B1364, float, BeatmapLevelSO self) {
	log("Called BeatmapLevelSO_get_shufflePeriod Hook!");
	return BeatmapLevelSO_get_shufflePeriod(self);
}

MAKE_HOOK(BeatmapLevelSO_get_previewAudioClip, 0x12B136C, void, BeatmapLevelSO self) {
	log("Called BeatmapLevelSO_get_previewAudioClip Hook!");
	return BeatmapLevelSO_get_previewAudioClip(self);
}

MAKE_HOOK(BeatmapLevelSO_get_previewStartTime, 0x12B1374, float, BeatmapLevelSO self) {
	log("Called BeatmapLevelSO_get_previewStartTime Hook!");
	return BeatmapLevelSO_get_previewStartTime(self);
}

MAKE_HOOK(BeatmapLevelSO_get_previewDuration, 0x12B137C, float, BeatmapLevelSO self) {
	log("Called BeatmapLevelSO_get_previewDuration Hook!");
	return BeatmapLevelSO_get_previewDuration(self);
}

MAKE_HOOK(BeatmapLevelSO_get_coverImageTexture2D, 0x12B1384, void, BeatmapLevelSO self) {
	log("Called BeatmapLevelSO_get_coverImageTexture2D Hook!");
	return BeatmapLevelSO_get_coverImageTexture2D(self);
}

MAKE_HOOK(BeatmapLevelSO_get_environmentSceneInfo, 0x12B138C, void, BeatmapLevelSO self) {
	log("Called BeatmapLevelSO_get_environmentSceneInfo Hook!");
	return BeatmapLevelSO_get_environmentSceneInfo(self);
}

MAKE_HOOK(BeatmapLevelSO_get_difficultyBeatmapSets, 0x12B1394, void, BeatmapLevelSO self) {
	log("Called BeatmapLevelSO_get_difficultyBeatmapSets Hook!");
	return BeatmapLevelSO_get_difficultyBeatmapSets(self);
}

MAKE_HOOK(BeatmapLevelSO_get_songDuration, 0x12B139C, float, BeatmapLevelSO self) {
	log("Called BeatmapLevelSO_get_songDuration Hook!");
	return BeatmapLevelSO_get_songDuration(self);
}

MAKE_HOOK(BeatmapLevelSO_GetPreviewAudioClipAsync, 0x12B13C8, void, BeatmapLevelSO self, void* cancellationToken) {
	log("Called BeatmapLevelSO_GetPreviewAudioClipAsync Hook!");
	return BeatmapLevelSO_GetPreviewAudioClipAsync(self, cancellationToken);
}

MAKE_HOOK(BeatmapLevelSO_GetCoverImageTexture2DAsync, 0x12B1508, void, BeatmapLevelSO self, void* cancellationToken) {
	log("Called BeatmapLevelSO_GetCoverImageTexture2DAsync Hook!");
	return BeatmapLevelSO_GetCoverImageTexture2DAsync(self, cancellationToken);
}

MAKE_HOOK(BeatmapLevelSO_get_beatmapLevelData, 0x129A3EC, void, BeatmapLevelSO self) {
	log("Called BeatmapLevelSO_get_beatmapLevelData Hook!");
	return BeatmapLevelSO_get_beatmapLevelData(self);
}

MAKE_HOOK(BeatmapLevelSO_get_beatmapCharacteristics, 0x12B1648, void, BeatmapLevelSO self) {
	log("Called BeatmapLevelSO_get_beatmapCharacteristics Hook!");
	return BeatmapLevelSO_get_beatmapCharacteristics(self);
}

MAKE_HOOK(BeatmapLevelSO_GetBeatmapLevelDataAsync, 0x12B1650, void, BeatmapLevelSO self, void* token) {
	log("Called BeatmapLevelSO_GetBeatmapLevelDataAsync Hook!");
	return BeatmapLevelSO_GetBeatmapLevelDataAsync(self, token);
}

MAKE_HOOK(BeatmapLevelSO_InitFull, 0x12B1788, void, BeatmapLevelSO self, void* levelID, void* songName, void* songSubName, void* songAuthorName, void* levelAuthorName, void* audioClip, float beatsPerMinute, float songTimeOffset, float shuffle, float shufflePeriod, float previewStartTime, float previewDuration, void* coverImageTexture2D, void* environmentSceneInfo, void* difficultyBeatmapSets) {
	log("Called BeatmapLevelSO_InitFull Hook!");
	BeatmapLevelSO_InitFull(self, levelID, songName, songSubName, songAuthorName, levelAuthorName, audioClip, beatsPerMinute, songTimeOffset, shuffle, shufflePeriod, previewStartTime, previewDuration, coverImageTexture2D, environmentSceneInfo, difficultyBeatmapSets);
}

MAKE_HOOK(BeatmapLevelSO_InitData, 0x12B1800, void, BeatmapLevelSO self) {
	log("Called BeatmapLevelSO_InitData Hook!");
	BeatmapLevelSO_InitData(self);
}

MAKE_HOOK(BeatmapLevelSO_OnEnable, 0x12B1A28, void, BeatmapLevelSO self) {
	log("Called BeatmapLevelSO_OnEnable Hook!");
	BeatmapLevelSO_OnEnable(self);
}

MAKE_HOOK(LevelPacksTableView_add_didSelectPackEvent, 0x12C0170, void, LevelPacksTableView self, void* value) {
	log("Called LevelPacksTableView_add_didSelectPackEvent Hook!");
	LevelPacksTableView_add_didSelectPackEvent(self, value);
}

MAKE_HOOK(LevelPacksTableView_remove_didSelectPackEvent, 0x12C027C, void, LevelPacksTableView self, void* value) {
	log("Called LevelPacksTableView_remove_didSelectPackEvent Hook!");
	LevelPacksTableView_remove_didSelectPackEvent(self, value);
}

MAKE_HOOK(LevelPacksTableView_Init, 0x12C0388, void, LevelPacksTableView self) {
	log("Called LevelPacksTableView_Init Hook!");
	LevelPacksTableView_Init(self);
}

MAKE_HOOK(LevelPacksTableView_SetData, 0x12C0530, void, LevelPacksTableView self, void* packCollection) {
	log("Called LevelPacksTableView_SetData Hook!");
	LevelPacksTableView_SetData(self, packCollection);
}

MAKE_HOOK(LevelPacksTableView_OnEnable, 0x12C05AC, void, LevelPacksTableView self) {
	log("Called LevelPacksTableView_OnEnable Hook!");
	LevelPacksTableView_OnEnable(self);
}

MAKE_HOOK(LevelPacksTableView_OnDisable, 0x12C0654, void, LevelPacksTableView self) {
	log("Called LevelPacksTableView_OnDisable Hook!");
	LevelPacksTableView_OnDisable(self);
}

MAKE_HOOK(LevelPacksTableView_OnDestroy, 0x12C06FC, void, LevelPacksTableView self) {
	log("Called LevelPacksTableView_OnDestroy Hook!");
	LevelPacksTableView_OnDestroy(self);
}

MAKE_HOOK(LevelPacksTableView_CellSize, 0x12C07B0, float, LevelPacksTableView self) {
	log("Called LevelPacksTableView_CellSize Hook!");
	return LevelPacksTableView_CellSize(self);
}

MAKE_HOOK(LevelPacksTableView_NumberOfCells, 0x12C07B8, int, LevelPacksTableView self) {
	log("Called LevelPacksTableView_NumberOfCells Hook!");
	return LevelPacksTableView_NumberOfCells(self);
}

MAKE_HOOK(LevelPacksTableView_CellForIdx, 0x12C08A8, void, LevelPacksTableView self, int idx) {
	log("Called LevelPacksTableView_CellForIdx Hook!");
	return LevelPacksTableView_CellForIdx(self, idx);
}

MAKE_HOOK(LevelPacksTableView_HandleDidSelectColumnEvent, 0x12C0C14, void, LevelPacksTableView self, void* tableView, int column) {
	log("Called LevelPacksTableView_HandleDidSelectColumnEvent Hook!");
	LevelPacksTableView_HandleDidSelectColumnEvent(self, tableView, column);
}

MAKE_HOOK(LevelPacksTableView_HandleAdditionalContentModelDidInvalidateData, 0x12C0D64, void, LevelPacksTableView self) {
	log("Called LevelPacksTableView_HandleAdditionalContentModelDidInvalidateData Hook!");
	LevelPacksTableView_HandleAdditionalContentModelDidInvalidateData(self);
}

MAKE_HOOK(LevelPacksTableView_CancelAsyncOperations, 0x12C0E54, void, LevelPacksTableView self) {
	log("Called LevelPacksTableView_CancelAsyncOperations Hook!");
	LevelPacksTableView_CancelAsyncOperations(self);
}

MAKE_HOOK(LevelPacksTableView_RefreshPacksAvailability, 0x12C1284, void, LevelPacksTableView self) {
	log("Called LevelPacksTableView_RefreshPacksAvailability Hook!");
	LevelPacksTableView_RefreshPacksAvailability(self);
}

MAKE_HOOK(LevelPacksTableView_SelectCellWithIdx, 0x12C1748, void, LevelPacksTableView self, int idx) {
	log("Called LevelPacksTableView_SelectCellWithIdx Hook!");
	LevelPacksTableView_SelectCellWithIdx(self, idx);
}

MAKE_HOOK(TextSegmentedControlCellNew_SelectionDidChange, 0x13636D0, void, TextSegmentedControlCellNew self, void* transitionType) {
	log("Called TextSegmentedControlCellNew_SelectionDidChange Hook!");
	TextSegmentedControlCellNew_SelectionDidChange(self, transitionType);
}

MAKE_HOOK(TextSegmentedControlCellNew_HighlightDidChange, 0x13638C4, void, TextSegmentedControlCellNew self, void* transitionType) {
	log("Called TextSegmentedControlCellNew_HighlightDidChange Hook!");
	TextSegmentedControlCellNew_HighlightDidChange(self, transitionType);
}

MAKE_HOOK(TextSegmentedControlCellNew_RefreshVisuals, 0x13636D4, void, TextSegmentedControlCellNew self) {
	log("Called TextSegmentedControlCellNew_RefreshVisuals Hook!");
	TextSegmentedControlCellNew_RefreshVisuals(self);
}

MAKE_HOOK(Toggle_add_didSwitchEvent, 0x1363A70, void, Toggle self, void* value) {
	log("Called Toggle_add_didSwitchEvent Hook!");
	Toggle_add_didSwitchEvent(self, value);
}

MAKE_HOOK(Toggle_remove_didSwitchEvent, 0x1363B7C, void, Toggle self, void* value) {
	log("Called Toggle_remove_didSwitchEvent Hook!");
	Toggle_remove_didSwitchEvent(self, value);
}

MAKE_HOOK(Toggle_get_isOn, 0x1363C88, char, Toggle self) {
	log("Called Toggle_get_isOn Hook!");
	return Toggle_get_isOn(self);
}

MAKE_HOOK(Toggle_set_isOn, 0x1363C90, void, Toggle self, char value) {
	log("Called Toggle_set_isOn Hook!");
	Toggle_set_isOn(self, value);
}

MAKE_HOOK(Toggle_Start, 0x1363ECC, void, Toggle self) {
	log("Called Toggle_Start Hook!");
	Toggle_Start(self);
}

MAKE_HOOK(Toggle_InternalToggle, 0x1363F3C, void, Toggle self) {
	log("Called Toggle_InternalToggle Hook!");
	Toggle_InternalToggle(self);
}

MAKE_HOOK(Toggle_RefreshColors, 0x1363C98, void, Toggle self) {
	log("Called Toggle_RefreshColors Hook!");
	Toggle_RefreshColors(self);
}

MAKE_HOOK(Toggle_OnPointerClick, 0x1363FE4, void, Toggle self, void* eventData) {
	log("Called Toggle_OnPointerClick Hook!");
	Toggle_OnPointerClick(self, eventData);
}

MAKE_HOOK(Toggle_OnSubmit, 0x13640D4, void, Toggle self, void* eventData) {
	log("Called Toggle_OnSubmit Hook!");
	Toggle_OnSubmit(self, eventData);
}

MAKE_HOOK(Toggle_OnPointerEnter, 0x1364198, void, Toggle self, void* eventData) {
	log("Called Toggle_OnPointerEnter Hook!");
	Toggle_OnPointerEnter(self, eventData);
}

MAKE_HOOK(Toggle_OnPointerExit, 0x13641A4, void, Toggle self, void* eventData) {
	log("Called Toggle_OnPointerExit Hook!");
	Toggle_OnPointerExit(self, eventData);
}

__attribute__((constructor)) void lib_main() {
	log("Attempting to install hook: BeatmapLevelSO_get_levelID at offset: 0x129C154");
	INSTALL_HOOK(BeatmapLevelSO_get_levelID);
	log("Attempting to install hook: BeatmapLevelSO_get_songName at offset: 0x12B132C");
	INSTALL_HOOK(BeatmapLevelSO_get_songName);
	log("Attempting to install hook: BeatmapLevelSO_get_songSubName at offset: 0x12B1334");
	INSTALL_HOOK(BeatmapLevelSO_get_songSubName);
	log("Attempting to install hook: BeatmapLevelSO_get_songAuthorName at offset: 0x12B133C");
	INSTALL_HOOK(BeatmapLevelSO_get_songAuthorName);
	log("Attempting to install hook: BeatmapLevelSO_get_levelAuthorName at offset: 0x12B1344");
	INSTALL_HOOK(BeatmapLevelSO_get_levelAuthorName);
	log("Attempting to install hook: BeatmapLevelSO_get_beatsPerMinute at offset: 0x12B134C");
	INSTALL_HOOK(BeatmapLevelSO_get_beatsPerMinute);
	log("Attempting to install hook: BeatmapLevelSO_get_songTimeOffset at offset: 0x12B1354");
	INSTALL_HOOK(BeatmapLevelSO_get_songTimeOffset);
	log("Attempting to install hook: BeatmapLevelSO_get_shuffle at offset: 0x12B135C");
	INSTALL_HOOK(BeatmapLevelSO_get_shuffle);
	log("Attempting to install hook: BeatmapLevelSO_get_shufflePeriod at offset: 0x12B1364");
	INSTALL_HOOK(BeatmapLevelSO_get_shufflePeriod);
	log("Attempting to install hook: BeatmapLevelSO_get_previewAudioClip at offset: 0x12B136C");
	INSTALL_HOOK(BeatmapLevelSO_get_previewAudioClip);
	log("Attempting to install hook: BeatmapLevelSO_get_previewStartTime at offset: 0x12B1374");
	INSTALL_HOOK(BeatmapLevelSO_get_previewStartTime);
	log("Attempting to install hook: BeatmapLevelSO_get_previewDuration at offset: 0x12B137C");
	INSTALL_HOOK(BeatmapLevelSO_get_previewDuration);
	log("Attempting to install hook: BeatmapLevelSO_get_coverImageTexture2D at offset: 0x12B1384");
	INSTALL_HOOK(BeatmapLevelSO_get_coverImageTexture2D);
	log("Attempting to install hook: BeatmapLevelSO_get_environmentSceneInfo at offset: 0x12B138C");
	INSTALL_HOOK(BeatmapLevelSO_get_environmentSceneInfo);
	log("Attempting to install hook: BeatmapLevelSO_get_difficultyBeatmapSets at offset: 0x12B1394");
	INSTALL_HOOK(BeatmapLevelSO_get_difficultyBeatmapSets);
	log("Attempting to install hook: BeatmapLevelSO_get_songDuration at offset: 0x12B139C");
	INSTALL_HOOK(BeatmapLevelSO_get_songDuration);
	log("Attempting to install hook: BeatmapLevelSO_GetPreviewAudioClipAsync at offset: 0x12B13C8");
	INSTALL_HOOK(BeatmapLevelSO_GetPreviewAudioClipAsync);
	log("Attempting to install hook: BeatmapLevelSO_GetCoverImageTexture2DAsync at offset: 0x12B1508");
	INSTALL_HOOK(BeatmapLevelSO_GetCoverImageTexture2DAsync);
	log("Attempting to install hook: BeatmapLevelSO_get_beatmapLevelData at offset: 0x129A3EC");
	INSTALL_HOOK(BeatmapLevelSO_get_beatmapLevelData);
	log("Attempting to install hook: BeatmapLevelSO_get_beatmapCharacteristics at offset: 0x12B1648");
	INSTALL_HOOK(BeatmapLevelSO_get_beatmapCharacteristics);
	log("Attempting to install hook: BeatmapLevelSO_GetBeatmapLevelDataAsync at offset: 0x12B1650");
	INSTALL_HOOK(BeatmapLevelSO_GetBeatmapLevelDataAsync);
	log("Attempting to install hook: BeatmapLevelSO_InitFull at offset: 0x12B1788");
	INSTALL_HOOK(BeatmapLevelSO_InitFull);
	log("Attempting to install hook: BeatmapLevelSO_InitData at offset: 0x12B1800");
	INSTALL_HOOK(BeatmapLevelSO_InitData);
	log("Attempting to install hook: BeatmapLevelSO_OnEnable at offset: 0x12B1A28");
	INSTALL_HOOK(BeatmapLevelSO_OnEnable);
	log("Attempting to install hook: LevelPacksTableView_add_didSelectPackEvent at offset: 0x12C0170");
	INSTALL_HOOK(LevelPacksTableView_add_didSelectPackEvent);
	log("Attempting to install hook: LevelPacksTableView_remove_didSelectPackEvent at offset: 0x12C027C");
	INSTALL_HOOK(LevelPacksTableView_remove_didSelectPackEvent);
	log("Attempting to install hook: LevelPacksTableView_Init at offset: 0x12C0388");
	INSTALL_HOOK(LevelPacksTableView_Init);
	log("Attempting to install hook: LevelPacksTableView_SetData at offset: 0x12C0530");
	INSTALL_HOOK(LevelPacksTableView_SetData);
	log("Attempting to install hook: LevelPacksTableView_OnEnable at offset: 0x12C05AC");
	INSTALL_HOOK(LevelPacksTableView_OnEnable);
	log("Attempting to install hook: LevelPacksTableView_OnDisable at offset: 0x12C0654");
	INSTALL_HOOK(LevelPacksTableView_OnDisable);
	log("Attempting to install hook: LevelPacksTableView_OnDestroy at offset: 0x12C06FC");
	INSTALL_HOOK(LevelPacksTableView_OnDestroy);
	log("Attempting to install hook: LevelPacksTableView_CellSize at offset: 0x12C07B0");
	INSTALL_HOOK(LevelPacksTableView_CellSize);
	log("Attempting to install hook: LevelPacksTableView_NumberOfCells at offset: 0x12C07B8");
	INSTALL_HOOK(LevelPacksTableView_NumberOfCells);
	log("Attempting to install hook: LevelPacksTableView_CellForIdx at offset: 0x12C08A8");
	INSTALL_HOOK(LevelPacksTableView_CellForIdx);
	log("Attempting to install hook: LevelPacksTableView_HandleDidSelectColumnEvent at offset: 0x12C0C14");
	INSTALL_HOOK(LevelPacksTableView_HandleDidSelectColumnEvent);
	log("Attempting to install hook: LevelPacksTableView_HandleAdditionalContentModelDidInvalidateData at offset: 0x12C0D64");
	INSTALL_HOOK(LevelPacksTableView_HandleAdditionalContentModelDidInvalidateData);
	log("Attempting to install hook: LevelPacksTableView_CancelAsyncOperations at offset: 0x12C0E54");
	INSTALL_HOOK(LevelPacksTableView_CancelAsyncOperations);
	log("Attempting to install hook: LevelPacksTableView_RefreshPacksAvailability at offset: 0x12C1284");
	INSTALL_HOOK(LevelPacksTableView_RefreshPacksAvailability);
	log("Attempting to install hook: LevelPacksTableView_SelectCellWithIdx at offset: 0x12C1748");
	INSTALL_HOOK(LevelPacksTableView_SelectCellWithIdx);
	log("Attempting to install hook: TextSegmentedControlCellNew_SelectionDidChange at offset: 0x13636D0");
	INSTALL_HOOK(TextSegmentedControlCellNew_SelectionDidChange);
	log("Attempting to install hook: TextSegmentedControlCellNew_HighlightDidChange at offset: 0x13638C4");
	INSTALL_HOOK(TextSegmentedControlCellNew_HighlightDidChange);
	log("Attempting to install hook: TextSegmentedControlCellNew_RefreshVisuals at offset: 0x13636D4");
	INSTALL_HOOK(TextSegmentedControlCellNew_RefreshVisuals);
	log("Attempting to install hook: Toggle_add_didSwitchEvent at offset: 0x1363A70");
	INSTALL_HOOK(Toggle_add_didSwitchEvent);
	log("Attempting to install hook: Toggle_remove_didSwitchEvent at offset: 0x1363B7C");
	INSTALL_HOOK(Toggle_remove_didSwitchEvent);
	log("Attempting to install hook: Toggle_get_isOn at offset: 0x1363C88");
	INSTALL_HOOK(Toggle_get_isOn);
	log("Attempting to install hook: Toggle_set_isOn at offset: 0x1363C90");
	INSTALL_HOOK(Toggle_set_isOn);
	log("Attempting to install hook: Toggle_Start at offset: 0x1363ECC");
	INSTALL_HOOK(Toggle_Start);
	log("Attempting to install hook: Toggle_InternalToggle at offset: 0x1363F3C");
	INSTALL_HOOK(Toggle_InternalToggle);
	log("Attempting to install hook: Toggle_RefreshColors at offset: 0x1363C98");
	INSTALL_HOOK(Toggle_RefreshColors);
	log("Attempting to install hook: Toggle_OnPointerClick at offset: 0x1363FE4");
	INSTALL_HOOK(Toggle_OnPointerClick);
	log("Attempting to install hook: Toggle_OnSubmit at offset: 0x13640D4");
	INSTALL_HOOK(Toggle_OnSubmit);
	log("Attempting to install hook: Toggle_OnPointerEnter at offset: 0x1364198");
	INSTALL_HOOK(Toggle_OnPointerEnter);
	log("Attempting to install hook: Toggle_OnPointerExit at offset: 0x13641A4");
	INSTALL_HOOK(Toggle_OnPointerExit);
	log("Complete!");
}
