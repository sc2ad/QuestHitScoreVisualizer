struct BeatmapLevelSO;
struct AudioClip;
typedef struct __attribute__((__packed__)) AudioClip {
	char _unused_data_useless[0xC];

	void* m_PCMReaderCallback;
	void* m_PCMSetPositionCallback;
} AudioClip_t;
struct BeatmapCharacteristicSO;
typedef struct __attribute__((__packed__)) BeatmapCharacteristicSO {
	char _unused_data_useless[0xC];

	void* _icon;
	cs_string* _hintText;
	cs_string* _characteristicName;
	cs_string* _serializedName;
	cs_string* _compoundIdPartName;
	int _sortingOrder;
} BeatmapCharacteristicSO_t;
struct GetBeatmapLevelDataResult;
typedef struct __attribute__((__packed__)) GetBeatmapLevelDataResult {
	int _result;
	void* _beatmapLevelData;
} GetBeatmapLevelDataResult_t;
typedef struct __attribute__((__packed__)) BeatmapLevelSO {
	char _unused_data_useless[0xC];

	cs_string* _levelID;
	cs_string* _songName;
	cs_string* _songSubName;
	cs_string* _songAuthorName;
	cs_string* _levelAuthorName;
	struct AudioClip* _audioClip;
	float _beatsPerMinute;
	float _songTimeOffset;
	float _shuffle;
	float _shufflePeriod;
	float _previewStartTime;
	float _previewDuration;
	void* _coverImageTexture2D;
	void* _environmentSceneInfo;
	void* _difficultyBeatmapSets;
	struct BeatmapCharacteristicSO* _beatmapCharacteristics;
	void* _beatmapLevelData;
	struct GetBeatmapLevelDataResult _getBeatmapLevelDataResult;
} BeatmapLevelSO_t;
struct LevelPacksTableView;
struct TableView;
struct Button;
typedef struct __attribute__((__packed__)) Button {
	char _unused_data_useless[0x94];

	void* m_OnClick;
} Button_t;
struct CellsGroup;
typedef struct __attribute__((__packed__)) CellsGroup {
	char _unused_data_useless[0x8];

	cs_string* reuseIdentifier;
	void* cells;
} CellsGroup_t;
struct ScrollRect;
struct Scrollbar;
struct Vector2;
typedef struct __attribute__((__packed__)) Vector2 {
	float x;
	float y;
} Vector2_t;
struct Coroutine;
typedef struct __attribute__((__packed__)) Scrollbar {
	char _unused_data_useless[0x94];

	void* m_HandleRect;
	int m_Direction;
	float m_Value;
	float m_Size;
	int m_NumberOfSteps;
	void* m_OnValueChanged;
	void* m_ContainerRect;
	struct Vector2 m_Offset;
	void* m_Tracker;
	void* m_PointerDownRepeat;
	char isPointerDownAndNotDragging;
} Scrollbar_t;
struct Bounds;
struct Vector3;
typedef struct __attribute__((__packed__)) Vector3 {
	float x;
	float y;
	float z;
} Vector3_t;
typedef struct __attribute__((__packed__)) Bounds {
	struct Vector3 m_Center;
	struct Vector3 m_Extents;
} Bounds_t;
typedef struct __attribute__((__packed__)) ScrollRect {
	char _unused_data_useless[0xC];

	void* m_Content;
	char m_Horizontal;
	char m_Vertical;
	int m_MovementType;
	float m_Elasticity;
	char m_Inertia;
	float m_DecelerationRate;
	float m_ScrollSensitivity;
	void* m_Viewport;
	struct Scrollbar* m_HorizontalScrollbar;
	struct Scrollbar* m_VerticalScrollbar;
	int m_HorizontalScrollbarVisibility;
	int m_VerticalScrollbarVisibility;
	float m_HorizontalScrollbarSpacing;
	float m_VerticalScrollbarSpacing;
	void* m_OnValueChanged;
	struct Vector2 m_PointerStartLocalCursor;
	struct Vector2 m_ContentStartPosition;
	void* m_ViewRect;
	struct Bounds m_ContentBounds;
	struct Bounds m_ViewBounds;
	struct Vector2 m_Velocity;
	char m_Dragging;
	struct Vector2 m_PrevPosition;
	struct Bounds m_PrevContentBounds;
	struct Bounds m_PrevViewBounds;
	char m_HasRebuiltLayout;
	char m_HSliderExpand;
	char m_VSliderExpand;
	float m_HSliderHeight;
	float m_VSliderWidth;
	void* m_Rect;
	void* m_HorizontalScrollbarRect;
	void* m_VerticalScrollbarRect;
	void* m_Tracker;
	struct Vector3 m_Corners;
} ScrollRect_t;
struct ButtonBinder;
typedef struct __attribute__((__packed__)) ButtonBinder {
	char _unused_data_useless[0x8];

	void* _bindings;
} ButtonBinder_t;
typedef struct __attribute__((__packed__)) TableView {
	char _unused_data_useless[0xC];

	char _hideScrollButtonsIfNotNeeded;
	struct Button* _pageUpButton;
	struct Button* _pageDownButton;
	char _alignToCenter;
	int _tableType;
	int _selectionType;
	struct CellsGroup* _preallocatedCells;
	void* didSelectCellWithIdxEvent;
	void* cellWasPressedEvent;
	struct ScrollRect* _scrollRect;
	void* _scrollRectTransform;
	void* _contentTransform;
	void* _dataSource;
	int _numberOfCells;
	float _cellSize;
	void* _visibleCells;
	void* _reusableCells;
	void* _selectedCellIdxs;
	int _prevMinIdx;
	int _prevMaxIdx;
	float _targetPosition;
	char _isInitialized;
	struct ButtonBinder* _buttonBinder;
} TableView_t;
struct LevelPackTableCell;
struct TextMeshProUGUI;
struct TMP_SubMeshUI;
struct TMP_FontAsset;
struct FaceInfo;
typedef struct __attribute__((__packed__)) FaceInfo {
	char _unused_data_useless[0x8];

	cs_string* Name;
	float PointSize;
	float Scale;
	int CharacterCount;
	float LineHeight;
	float Baseline;
	float Ascender;
	float CapHeight;
	float Descender;
	float CenterLine;
	float SuperscriptOffset;
	float SubscriptOffset;
	float SubSize;
	float Underline;
	float UnderlineThickness;
	float strikethrough;
	float strikethroughThickness;
	float TabWidth;
	float Padding;
	float AtlasWidth;
	float AtlasHeight;
} FaceInfo_t;
struct KerningTable;
typedef struct __attribute__((__packed__)) KerningTable {
	char _unused_data_useless[0x8];

	void* kerningPairs;
} KerningTable_t;
struct KerningPair;
struct GlyphValueRecord;
typedef struct __attribute__((__packed__)) GlyphValueRecord {
	float xPlacement;
	float yPlacement;
	float xAdvance;
	float yAdvance;
} GlyphValueRecord_t;
typedef struct __attribute__((__packed__)) KerningPair {
	char _unused_data_useless[0x8];

	unsigned int m_FirstGlyph;
	struct GlyphValueRecord m_FirstGlyphAdjustments;
	unsigned int m_SecondGlyph;
	struct GlyphValueRecord m_SecondGlyphAdjustments;
	float xOffset;
} KerningPair_t;
struct FontAssetCreationSettings;
typedef struct __attribute__((__packed__)) FontAssetCreationSettings {
	cs_string* sourceFontFileName;
	cs_string* sourceFontFileGUID;
	int pointSizeSamplingMode;
	int pointSize;
	int padding;
	int packingMode;
	int atlasWidth;
	int atlasHeight;
	int characterSetSelectionMode;
	cs_string* characterSequence;
	cs_string* referencedFontAssetGUID;
	cs_string* referencedTextAssetGUID;
	int fontStyle;
	float fontStyleModifier;
	int renderMode;
	char includeFontFeatures;
} FontAssetCreationSettings_t;
struct TMP_FontWeights;
typedef struct __attribute__((__packed__)) TMP_FontWeights {
	struct TMP_FontAsset* regularTypeface;
	struct TMP_FontAsset* italicTypeface;
} TMP_FontWeights_t;
typedef struct __attribute__((__packed__)) TMP_FontAsset {
	char _unused_data_useless[0x18];

	int fontAssetType;
	struct FaceInfo* m_fontInfo;
	void* atlas;
	void* m_glyphInfoList;
	void* m_characterDictionary;
	void* m_kerningDictionary;
	struct KerningTable* m_kerningInfo;
	struct KerningPair* m_kerningPair;
	void* fallbackFontAssets;
	struct FontAssetCreationSettings m_CreationSettings;
	struct TMP_FontWeights fontWeights;
	void* m_characterSet;
	float normalStyle;
	float normalSpacingOffset;
	float boldStyle;
	float boldSpacing;
	char italicStyle;
	char tabSize;
	char m_oldTabSize;
} TMP_FontAsset_t;
struct TMP_SpriteAsset;
typedef struct __attribute__((__packed__)) TMP_SpriteAsset {
	char _unused_data_useless[0x18];

	void* m_UnicodeLookup;
	void* m_NameLookup;
	void* spriteSheet;
	void* spriteInfoList;
	void* fallbackSpriteAssets;
} TMP_SpriteAsset_t;
struct CanvasRenderer;
typedef struct __attribute__((__packed__)) CanvasRenderer {
	char _unused_data_useless[0xC];

	char isMask_k__BackingField;
} CanvasRenderer_t;
typedef struct __attribute__((__packed__)) TMP_SubMeshUI {
	char _unused_data_useless[0x64];

	struct TMP_FontAsset* m_fontAsset;
	struct TMP_SpriteAsset* m_spriteAsset;
	void* m_material;
	void* m_sharedMaterial;
	void* m_fallbackMaterial;
	void* m_fallbackSourceMaterial;
	char m_isDefaultMaterial;
	float m_padding;
	struct CanvasRenderer* m_canvasRenderer;
	void* m_mesh;
	struct TextMeshProUGUI* m_TextComponent;
	char m_isRegisteredForEvents;
	char m_materialDirty;
	int m_materialReferenceIndex;
} TMP_SubMeshUI_t;
struct Vector4;
typedef struct __attribute__((__packed__)) Vector4 {
	float x;
	float y;
	float z;
	float w;
} Vector4_t;
struct Matrix4x4;
typedef struct __attribute__((__packed__)) Matrix4x4 {
	float m00;
	float m10;
	float m20;
	float m30;
	float m01;
	float m11;
	float m21;
	float m31;
	float m02;
	float m12;
	float m22;
	float m32;
	float m03;
	float m13;
	float m23;
	float m33;
} Matrix4x4_t;
typedef struct __attribute__((__packed__)) TextMeshProUGUI {
	char _unused_data_useless[0x86C];

	char m_isRebuildingLayout;
	char m_hasFontAssetChanged;
	struct TMP_SubMeshUI* m_subTextObjects;
	float m_previousLossyScaleY;
	struct Vector3 m_RectTransformCorners;
	struct CanvasRenderer* m_canvasRenderer;
	void* m_canvas;
	char m_isFirstAllocation;
	int m_max_characters;
	char m_isMaskingEnabled;
	void* m_baseMaterial;
	char m_isScrollRegionSet;
	int m_stencilID;
	struct Vector4 m_maskOffset;
	struct Matrix4x4 m_EnvMapMatrix;
	char m_isRegisteredForEvents;
	int m_recursiveCountA;
	int loopCountA;
} TextMeshProUGUI_t;
struct Image;
typedef struct __attribute__((__packed__)) Image {
	char _unused_data_useless[0x64];

	void* m_Sprite;
	void* m_OverrideSprite;
	int m_Type;
	char m_PreserveAspect;
	char m_FillCenter;
	int m_FillMethod;
	float m_FillAmount;
	char m_FillClockwise;
	int m_FillOrigin;
	float m_AlphaHitTestMinimumThreshold;
	char m_Tracked;
	char m_UseSpriteMesh;
} Image_t;
typedef struct __attribute__((__packed__)) LevelPackTableCell {
	char _unused_data_useless[0x24];

	struct TextMeshProUGUI* _packNameText;
	struct TextMeshProUGUI* _infoText;
	struct Image* _coverImage;
	struct Image* _selectionImage;
	void* _newPromoRibbonObjects;
	void* _cancellationTokenSource;
} LevelPackTableCell_t;
struct AdditionalContentModelSO;
struct TestPlatformAdditionalContentHandler;
struct Entitlement;
typedef struct __attribute__((__packed__)) Entitlement {
	char _unused_data_useless[0x8];

	cs_string* id;
	int status;
} Entitlement_t;
typedef struct __attribute__((__packed__)) TestPlatformAdditionalContentHandler {
	char _unused_data_useless[0xC];

	struct Entitlement* _levelsEntitlements;
	struct Entitlement* _levelPacksEntitlements;
	char _packBetterBuyThanLevel;
	void* didInvalidateDataEvent;
} TestPlatformAdditionalContentHandler_t;
struct PS4LevelProductsModelSO;
struct LevelPackProductData;
struct LevelProductData;
typedef struct __attribute__((__packed__)) LevelProductData {
	char _unused_data_useless[0x8];

	cs_string* _entitlementLabel;
	cs_string* _productLabel;
	cs_string* _levelId;
} LevelProductData_t;
typedef struct __attribute__((__packed__)) LevelPackProductData {
	char _unused_data_useless[0x8];

	cs_string* _productLabel;
	cs_string* _categoryLabel;
	cs_string* _packId;
	struct LevelProductData* _levelProductsData;
} LevelPackProductData_t;
typedef struct __attribute__((__packed__)) PS4LevelProductsModelSO {
	char _unused_data_useless[0xC];

	struct LevelPackProductData* _levelPackProductsData;
	float _packLevelPriceDiscountMul;
	void* _levelIdToProductData;
	void* _levelPackIdToProductData;
} PS4LevelProductsModelSO_t;
struct OculusLevelProductsModelSO;
typedef struct __attribute__((__packed__)) OculusLevelProductsModelSO {
	char _unused_data_useless[0xC];

	struct LevelPackProductData* _levelPackProductsData;
	void* _levelIdToProductData;
	void* _levelPackIdToProductData;
	void* _assetFileToSku;
} OculusLevelProductsModelSO_t;
struct SteamLevelProductsModelSO;
typedef struct __attribute__((__packed__)) SteamLevelProductsModelSO {
	char _unused_data_useless[0xC];

	struct LevelPackProductData* _levelPackProductsData;
	void* _levelIdToProductData;
	void* _levelPackIdToProductData;
} SteamLevelProductsModelSO_t;
typedef struct __attribute__((__packed__)) AdditionalContentModelSO {
	char _unused_data_useless[0xC];

	struct TestPlatformAdditionalContentHandler* _testPlatformAdditionalContentHandler;
	struct PS4LevelProductsModelSO* _ps4LevelProductsModel;
	struct OculusLevelProductsModelSO* _oculusLevelProductsModel;
	struct SteamLevelProductsModelSO* _steamLevelProductsModel;
	void* _alwaysOwnedContentModel;
	void* didInvalidateDataEvent;
	void* _platformAdditionalContentHandler;
	void* _alwaysOwnedBeatmapLevelIds;
	void* _alwaysOwnedPacksIds;
} AdditionalContentModelSO_t;
typedef struct __attribute__((__packed__)) LevelPacksTableView {
	char _unused_data_useless[0xC];

	struct TableView* _tableView;
	struct LevelPackTableCell* _cellPrefab;
	cs_string* _cellReuseIdentifier;
	float _cellWidth;
	struct AdditionalContentModelSO* _additionalContentModel;
	void* _promoPackIDStrings;
	void* didSelectPackEvent;
	void* _promoPackIDs;
	void* _levelPackCollection;
	char _isInitialized;
	int _selectedColumn;
} LevelPacksTableView_t;
struct TextSegmentedControlCellNew;
struct Color;
typedef struct __attribute__((__packed__)) Color {
	float r;
	float g;
	float b;
	float a;
} Color_t;
typedef struct __attribute__((__packed__)) TextSegmentedControlCellNew {
	char _unused_data_useless[0x20];

	struct Image* _bgImage;
	struct Color _normalTextColor;
	struct Color _selectedTextColor;
	struct Color _highlightTextColor;
	struct Color _selectedHighlightTextColor;
	struct Color _normalBGColor;
	struct Color _selectedBGColor;
	struct Color _highlightBGColor;
	struct Color _selectedHighlightBGColor;
} TextSegmentedControlCellNew_t;
struct Toggle;
struct Signal;
typedef struct __attribute__((__packed__)) Signal {
	char _unused_data_useless[0xC];

	void* _event;
} Signal_t;
typedef struct __attribute__((__packed__)) Toggle {
	char _unused_data_useless[0xC];

	cs_string* _onText;
	cs_string* _offText;
	struct Color _onTextColor;
	struct Color _offTextColor;
	struct Color _highlightColor;
	struct Color _selectedColor;
	struct Signal* _toggleWasPressedSignal;
	struct Image* _offImage;
	struct Image* _onImage;
	struct TextMeshProUGUI* _offTextUI;
	struct TextMeshProUGUI* _onTextUI;
	void* didSwitchEvent;
	char _isOn;
	char _isHighlighted;
} Toggle_t;
struct TableCell;
typedef struct __attribute__((__packed__)) TableCell {
	char _unused_data_useless[0xC];

	struct Signal* _tableCellWasPressedSignal;
	char _canSelectSelectedCell;
	cs_string* _reuseIdentifier;
	int _idx;
	void* _tableCellOwner;
	char _selected;
	char _highlighted;
} TableCell_t;
