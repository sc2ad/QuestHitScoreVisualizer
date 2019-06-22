struct CaptureAudioToWav;
typedef struct __attribute__((__packed__)) CaptureAudioToWav {
	char _unused_data_useless[0xC];

	cs_string* _fileName;
	int _sampleRate;
	int _headerSize;
	char _recording;
	void* _fileStream;
} CaptureAudioToWav_t;
struct DroppedFramesLabel;
struct TextMeshProUGUI;
struct TMP_SubMeshUI;
struct TMP_FontAsset;
enum FontAssetTypes {
	FontAssetTypes_None,
	FontAssetTypes_SDF,
	FontAssetTypes_Bitmap
};
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

	enum FontAssetTypes fontAssetType;
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
struct Vector3;
typedef struct __attribute__((__packed__)) Vector3 {
	float x;
	float y;
	float z;
} Vector3_t;
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
typedef struct __attribute__((__packed__)) DroppedFramesLabel {
	char _unused_data_useless[0xC];

	struct TextMeshProUGUI* _text;
	int _expectedFrameRate;
	int _resetInterval;
	int _totalNumberOfDroppedFrames;
	float _syncedFrameTime;
	float _intervalTime;
	float _maxFrameTimeInInterval;
	int _frameCountInInterval;
} DroppedFramesLabel_t;
struct Billboard;
enum RotationMode {
	RotationMode_AllAxis,
	RotationMode_XAxis,
	RotationMode_YAxis,
	RotationMode_ZAxis
};
typedef struct __attribute__((__packed__)) Billboard {
	char _unused_data_useless[0xC];

	enum RotationMode _rotationMode;
	char _flipDirection;
	void* _transform;
} Billboard_t;
struct CameraDepthTextureMode;
enum DepthTextureMode {
	DepthTextureMode_None,
	DepthTextureMode_Depth,
	DepthTextureMode_DepthNormals,
	DepthTextureMode_MotionVectors
};
typedef struct __attribute__((__packed__)) CameraDepthTextureMode {
	char _unused_data_useless[0xC];

	enum DepthTextureMode _depthTextureMode;
} CameraDepthTextureMode_t;
struct ClickButtonWithCommandArgument;
struct Button;
typedef struct __attribute__((__packed__)) Button {
	char _unused_data_useless[0x94];

	void* m_OnClick;
} Button_t;
typedef struct __attribute__((__packed__)) ClickButtonWithCommandArgument {
	char _unused_data_useless[0xC];

	cs_string* _argument;
	struct Button* _button;
} ClickButtonWithCommandArgument_t;
struct Ease01;
typedef struct __attribute__((__packed__)) Ease01 {
	char _unused_data_useless[0xC];

	void* _easeValue;
	void* _fadeInCurve;
	void* _fadeOutCurve;
	float _fadeInStartDelay;
	float _defaultFadeOutDuration;
	float _defaultFadeInDuration;
	void* _coroutine;
} Ease01_t;
struct EnableComponentWithCommandArgument;
typedef struct __attribute__((__packed__)) EnableComponentWithCommandArgument {
	char _unused_data_useless[0xC];

	cs_string* _argument;
	void* _component;
} EnableComponentWithCommandArgument_t;
struct EnableEmmisionOnVisible;
typedef struct __attribute__((__packed__)) EnableEmmisionOnVisible {
	char _unused_data_useless[0xC];

	void* _particleSystems;
	void* _emmisionModules;
} EnableEmmisionOnVisible_t;
struct FlexyFollowAndRotate;
typedef struct __attribute__((__packed__)) FlexyFollowAndRotate {
	char _unused_data_useless[0xC];

	void* _target;
	float _smooth;
} FlexyFollowAndRotate_t;
struct MarkableUIButton;
typedef struct __attribute__((__packed__)) MarkableUIButton {
	char _unused_data_useless[0xC];

	void* _animator;
	char _marked;
	int _markedTriggerId;
} MarkableUIButton_t;
struct RandomAnimationStartTime;
typedef struct __attribute__((__packed__)) RandomAnimationStartTime {
	char _unused_data_useless[0xC];

	void* _animator;
	cs_string* _stateName;
} RandomAnimationStartTime_t;
struct ResetPlayerPrefsOnButton;
enum KeyCode {
	KeyCode_None,
	KeyCode_Backspace,
	KeyCode_Delete,
	KeyCode_Tab,
	KeyCode_Clear,
	KeyCode_Return,
	KeyCode_Pause,
	KeyCode_Escape,
	KeyCode_Space,
	KeyCode_Keypad0,
	KeyCode_Keypad1,
	KeyCode_Keypad2,
	KeyCode_Keypad3,
	KeyCode_Keypad4,
	KeyCode_Keypad5,
	KeyCode_Keypad6,
	KeyCode_Keypad7,
	KeyCode_Keypad8,
	KeyCode_Keypad9,
	KeyCode_KeypadPeriod,
	KeyCode_KeypadDivide,
	KeyCode_KeypadMultiply,
	KeyCode_KeypadMinus,
	KeyCode_KeypadPlus,
	KeyCode_KeypadEnter,
	KeyCode_KeypadEquals,
	KeyCode_UpArrow,
	KeyCode_DownArrow,
	KeyCode_RightArrow,
	KeyCode_LeftArrow,
	KeyCode_Insert,
	KeyCode_Home,
	KeyCode_End,
	KeyCode_PageUp,
	KeyCode_PageDown,
	KeyCode_F1,
	KeyCode_F2,
	KeyCode_F3,
	KeyCode_F4,
	KeyCode_F5,
	KeyCode_F6,
	KeyCode_F7,
	KeyCode_F8,
	KeyCode_F9,
	KeyCode_F10,
	KeyCode_F11,
	KeyCode_F12,
	KeyCode_F13,
	KeyCode_F14,
	KeyCode_F15,
	KeyCode_Alpha0,
	KeyCode_Alpha1,
	KeyCode_Alpha2,
	KeyCode_Alpha3,
	KeyCode_Alpha4,
	KeyCode_Alpha5,
	KeyCode_Alpha6,
	KeyCode_Alpha7,
	KeyCode_Alpha8,
	KeyCode_Alpha9,
	KeyCode_Exclaim,
	KeyCode_DoubleQuote,
	KeyCode_Hash,
	KeyCode_Dollar,
	KeyCode_Percent,
	KeyCode_Ampersand,
	KeyCode_Quote,
	KeyCode_LeftParen,
	KeyCode_RightParen,
	KeyCode_Asterisk,
	KeyCode_Plus,
	KeyCode_Comma,
	KeyCode_Minus,
	KeyCode_Period,
	KeyCode_Slash,
	KeyCode_Colon,
	KeyCode_Semicolon,
	KeyCode_Less,
	KeyCode_Equals,
	KeyCode_Greater,
	KeyCode_Question,
	KeyCode_At,
	KeyCode_LeftBracket,
	KeyCode_Backslash,
	KeyCode_RightBracket,
	KeyCode_Caret,
	KeyCode_Underscore,
	KeyCode_BackQuote,
	KeyCode_A,
	KeyCode_B,
	KeyCode_C,
	KeyCode_D,
	KeyCode_E,
	KeyCode_F,
	KeyCode_G,
	KeyCode_H,
	KeyCode_I,
	KeyCode_J,
	KeyCode_K,
	KeyCode_L,
	KeyCode_M,
	KeyCode_N,
	KeyCode_O,
	KeyCode_P,
	KeyCode_Q,
	KeyCode_R,
	KeyCode_S,
	KeyCode_T,
	KeyCode_U,
	KeyCode_V,
	KeyCode_W,
	KeyCode_X,
	KeyCode_Y,
	KeyCode_Z,
	KeyCode_LeftCurlyBracket,
	KeyCode_Pipe,
	KeyCode_RightCurlyBracket,
	KeyCode_Tilde,
	KeyCode_Numlock,
	KeyCode_CapsLock,
	KeyCode_ScrollLock,
	KeyCode_RightShift,
	KeyCode_LeftShift,
	KeyCode_RightControl,
	KeyCode_LeftControl,
	KeyCode_RightAlt,
	KeyCode_LeftAlt,
	KeyCode_LeftCommand,
	KeyCode_LeftApple,
	KeyCode_LeftWindows,
	KeyCode_RightCommand,
	KeyCode_RightApple,
	KeyCode_RightWindows,
	KeyCode_AltGr,
	KeyCode_Help,
	KeyCode_Print,
	KeyCode_SysReq,
	KeyCode_Break,
	KeyCode_Menu,
	KeyCode_Mouse0,
	KeyCode_Mouse1,
	KeyCode_Mouse2,
	KeyCode_Mouse3,
	KeyCode_Mouse4,
	KeyCode_Mouse5,
	KeyCode_Mouse6,
	KeyCode_JoystickButton0,
	KeyCode_JoystickButton1,
	KeyCode_JoystickButton2,
	KeyCode_JoystickButton3,
	KeyCode_JoystickButton4,
	KeyCode_JoystickButton5,
	KeyCode_JoystickButton6,
	KeyCode_JoystickButton7,
	KeyCode_JoystickButton8,
	KeyCode_JoystickButton9,
	KeyCode_JoystickButton10,
	KeyCode_JoystickButton11,
	KeyCode_JoystickButton12,
	KeyCode_JoystickButton13,
	KeyCode_JoystickButton14,
	KeyCode_JoystickButton15,
	KeyCode_JoystickButton16,
	KeyCode_JoystickButton17,
	KeyCode_JoystickButton18,
	KeyCode_JoystickButton19,
	KeyCode_Joystick1Button0,
	KeyCode_Joystick1Button1,
	KeyCode_Joystick1Button2,
	KeyCode_Joystick1Button3,
	KeyCode_Joystick1Button4,
	KeyCode_Joystick1Button5,
	KeyCode_Joystick1Button6,
	KeyCode_Joystick1Button7,
	KeyCode_Joystick1Button8,
	KeyCode_Joystick1Button9,
	KeyCode_Joystick1Button10,
	KeyCode_Joystick1Button11,
	KeyCode_Joystick1Button12,
	KeyCode_Joystick1Button13,
	KeyCode_Joystick1Button14,
	KeyCode_Joystick1Button15,
	KeyCode_Joystick1Button16,
	KeyCode_Joystick1Button17,
	KeyCode_Joystick1Button18,
	KeyCode_Joystick1Button19,
	KeyCode_Joystick2Button0,
	KeyCode_Joystick2Button1,
	KeyCode_Joystick2Button2,
	KeyCode_Joystick2Button3,
	KeyCode_Joystick2Button4,
	KeyCode_Joystick2Button5,
	KeyCode_Joystick2Button6,
	KeyCode_Joystick2Button7,
	KeyCode_Joystick2Button8,
	KeyCode_Joystick2Button9,
	KeyCode_Joystick2Button10,
	KeyCode_Joystick2Button11,
	KeyCode_Joystick2Button12,
	KeyCode_Joystick2Button13,
	KeyCode_Joystick2Button14,
	KeyCode_Joystick2Button15,
	KeyCode_Joystick2Button16,
	KeyCode_Joystick2Button17,
	KeyCode_Joystick2Button18,
	KeyCode_Joystick2Button19,
	KeyCode_Joystick3Button0,
	KeyCode_Joystick3Button1,
	KeyCode_Joystick3Button2,
	KeyCode_Joystick3Button3,
	KeyCode_Joystick3Button4,
	KeyCode_Joystick3Button5,
	KeyCode_Joystick3Button6,
	KeyCode_Joystick3Button7,
	KeyCode_Joystick3Button8,
	KeyCode_Joystick3Button9,
	KeyCode_Joystick3Button10,
	KeyCode_Joystick3Button11,
	KeyCode_Joystick3Button12,
	KeyCode_Joystick3Button13,
	KeyCode_Joystick3Button14,
	KeyCode_Joystick3Button15,
	KeyCode_Joystick3Button16,
	KeyCode_Joystick3Button17,
	KeyCode_Joystick3Button18,
	KeyCode_Joystick3Button19,
	KeyCode_Joystick4Button0,
	KeyCode_Joystick4Button1,
	KeyCode_Joystick4Button2,
	KeyCode_Joystick4Button3,
	KeyCode_Joystick4Button4,
	KeyCode_Joystick4Button5,
	KeyCode_Joystick4Button6,
	KeyCode_Joystick4Button7,
	KeyCode_Joystick4Button8,
	KeyCode_Joystick4Button9,
	KeyCode_Joystick4Button10,
	KeyCode_Joystick4Button11,
	KeyCode_Joystick4Button12,
	KeyCode_Joystick4Button13,
	KeyCode_Joystick4Button14,
	KeyCode_Joystick4Button15,
	KeyCode_Joystick4Button16,
	KeyCode_Joystick4Button17,
	KeyCode_Joystick4Button18,
	KeyCode_Joystick4Button19,
	KeyCode_Joystick5Button0,
	KeyCode_Joystick5Button1,
	KeyCode_Joystick5Button2,
	KeyCode_Joystick5Button3,
	KeyCode_Joystick5Button4,
	KeyCode_Joystick5Button5,
	KeyCode_Joystick5Button6,
	KeyCode_Joystick5Button7,
	KeyCode_Joystick5Button8,
	KeyCode_Joystick5Button9,
	KeyCode_Joystick5Button10,
	KeyCode_Joystick5Button11,
	KeyCode_Joystick5Button12,
	KeyCode_Joystick5Button13,
	KeyCode_Joystick5Button14,
	KeyCode_Joystick5Button15,
	KeyCode_Joystick5Button16,
	KeyCode_Joystick5Button17,
	KeyCode_Joystick5Button18,
	KeyCode_Joystick5Button19,
	KeyCode_Joystick6Button0,
	KeyCode_Joystick6Button1,
	KeyCode_Joystick6Button2,
	KeyCode_Joystick6Button3,
	KeyCode_Joystick6Button4,
	KeyCode_Joystick6Button5,
	KeyCode_Joystick6Button6,
	KeyCode_Joystick6Button7,
	KeyCode_Joystick6Button8,
	KeyCode_Joystick6Button9,
	KeyCode_Joystick6Button10,
	KeyCode_Joystick6Button11,
	KeyCode_Joystick6Button12,
	KeyCode_Joystick6Button13,
	KeyCode_Joystick6Button14,
	KeyCode_Joystick6Button15,
	KeyCode_Joystick6Button16,
	KeyCode_Joystick6Button17,
	KeyCode_Joystick6Button18,
	KeyCode_Joystick6Button19,
	KeyCode_Joystick7Button0,
	KeyCode_Joystick7Button1,
	KeyCode_Joystick7Button2,
	KeyCode_Joystick7Button3,
	KeyCode_Joystick7Button4,
	KeyCode_Joystick7Button5,
	KeyCode_Joystick7Button6,
	KeyCode_Joystick7Button7,
	KeyCode_Joystick7Button8,
	KeyCode_Joystick7Button9,
	KeyCode_Joystick7Button10,
	KeyCode_Joystick7Button11,
	KeyCode_Joystick7Button12,
	KeyCode_Joystick7Button13,
	KeyCode_Joystick7Button14,
	KeyCode_Joystick7Button15,
	KeyCode_Joystick7Button16,
	KeyCode_Joystick7Button17,
	KeyCode_Joystick7Button18,
	KeyCode_Joystick7Button19,
	KeyCode_Joystick8Button0,
	KeyCode_Joystick8Button1,
	KeyCode_Joystick8Button2,
	KeyCode_Joystick8Button3,
	KeyCode_Joystick8Button4,
	KeyCode_Joystick8Button5,
	KeyCode_Joystick8Button6,
	KeyCode_Joystick8Button7,
	KeyCode_Joystick8Button8,
	KeyCode_Joystick8Button9,
	KeyCode_Joystick8Button10,
	KeyCode_Joystick8Button11,
	KeyCode_Joystick8Button12,
	KeyCode_Joystick8Button13,
	KeyCode_Joystick8Button14,
	KeyCode_Joystick8Button15,
	KeyCode_Joystick8Button16,
	KeyCode_Joystick8Button17,
	KeyCode_Joystick8Button18,
	KeyCode_Joystick8Button19
};
typedef struct __attribute__((__packed__)) ResetPlayerPrefsOnButton {
	char _unused_data_useless[0xC];

	enum KeyCode _keyCode;
} ResetPlayerPrefsOnButton_t;
struct ScreenshotRecorder;
enum RecordingType {
	RecordingType_Sequence,
	RecordingType_Stereo360Sequence,
	RecordingType_Mono360Sequence,
	RecordingType_F10ForScreenshot,
	RecordingType_Interval,
	RecordingType_ScreenshotOnPause
};
typedef struct __attribute__((__packed__)) ScreenshotRecorder {
	char _unused_data_useless[0xC];

	cs_string* _folder;
	void* _camera;
	int _frameRate;
	char _forceFixedFramerate;
	int _interval;
	enum RecordingType _recordingType;
	char _pauseWithPButton;
	int _antiAlias;
	int _screenshotWidth;
	int _screenshotHeight;
	int _counter;
	float _originalTimeScale;
	char _paused;
	int _frameNum;
	void* _cubemapLeftEye;
	void* _cubemapRighEye;
	void* _equirectTexture;
} ScreenshotRecorder_t;
struct EnviromentSceneInfoColectionSO;
typedef struct __attribute__((__packed__)) EnviromentSceneInfoColectionSO {
	char _unused_data_useless[0xC];

	void* _enviromentSceneInfos;
} EnviromentSceneInfoColectionSO_t;
struct GameScenesManagerSO;
struct Signal;
typedef struct __attribute__((__packed__)) Signal {
	char _unused_data_useless[0xC];

	void* _event;
} Signal_t;
struct GameScenesManager;
typedef struct __attribute__((__packed__)) GameScenesManager {
	char _unused_data_useless[0xC];

	void* transitionDidStartEvent;
	void* beforeDismissingScenesEvent;
	void* transitionDidFinishEvent;
	char _inTransition;
	void* _scenesStack;
	cs_string* _emptyTransitionSceneName;
} GameScenesManager_t;
typedef struct __attribute__((__packed__)) GameScenesManagerSO {
	char _unused_data_useless[0xC];

	void* _emptyTransitionSceneInfo;
	void* _transitionDidStartSignal;
	struct Signal* _transitionDidFinishSignal;
	struct Signal* _beforeDismissingScenesSignal;
	void* _scenesSetupData;
	struct GameScenesManager* _executor;
} GameScenesManagerSO_t;
struct TestSceneSetupDataInstallerStarter;
typedef struct __attribute__((__packed__)) TestSceneSetupDataInstallerStarter {
	char _unused_data_useless[0xC];

	void* _installers;
} TestSceneSetupDataInstallerStarter_t;
struct SignalListener;
struct UnityEvent;
typedef struct __attribute__((__packed__)) UnityEvent {
	char _unused_data_useless[0x18];

	void* m_InvokeArray;
} UnityEvent_t;
typedef struct __attribute__((__packed__)) SignalListener {
	char _unused_data_useless[0xC];

	struct Signal* _signal;
	struct UnityEvent* _unityEvent;
} SignalListener_t;
struct SignalOnUIButtonClick;
typedef struct __attribute__((__packed__)) SignalOnUIButtonClick {
	char _unused_data_useless[0xC];

	struct Signal* _buttonClickedSignal;
	struct Button* _button;
} SignalOnUIButtonClick_t;
struct VRController;
enum XRNode {
	XRNode_LeftEye,
	XRNode_RightEye,
	XRNode_CenterEye,
	XRNode_Head,
	XRNode_LeftHand,
	XRNode_RightHand,
	XRNode_GameController,
	XRNode_TrackingReference,
	XRNode_HardwareTracker
};
typedef struct __attribute__((__packed__)) VRController {
	char _unused_data_useless[0xC];

	enum XRNode _node;
	struct Vector3 _lastTrackedPosition;
} VRController_t;
struct CampaignFlowCoordinator;
typedef struct __attribute__((__packed__)) CampaignFlowCoordinator {
	char _unused_data_useless[0x44];

	struct MenuTransitionsHelperSO* _menuTransitionsHelper;
	struct CampaignProgressModelSO* _campaignProgressModel;
	struct PlayerDataModelSO* _playerDataModel;
	struct MenuLightsPresetSO* _defaultLightsPreset;
	struct MenuLightsPresetSO* _resultsLightsPreset;
	struct MenuLightsPresetSO* _newObjectiveLightsPreset;
	struct MenuLightsManager* _menuLightsManager;
	struct DismissableNavigationController* _navigationController;
	struct MissionSelectionMapViewController* _missionSelectionMapViewController;
	struct MissionLevelDetailViewController* _missionLevelDetailViewController;
	struct MissionResultsViewController* _missionResultsViewController;
	struct PlayerSettingsViewController* _playerSettingsViewController;
	struct MissionHelpViewController* _missionHelpViewController;
	void* didFinishEvent;
	void* didUpdateOverallStatsDataWithLevelCompletionResultsEvent;
	char _showCredits;
} CampaignFlowCoordinator_t;
struct VRInteractable;
typedef struct __attribute__((__packed__)) VRInteractable {
	char _unused_data_useless[0xC];

	char _interactable;
} VRInteractable_t;
struct BloomRenderer;
struct Level;
typedef struct __attribute__((__packed__)) Level {
	void* down;
	void* up;
} Level_t;
typedef struct __attribute__((__packed__)) BloomRenderer {
	char _unused_data_useless[0xC];

	void* _shader;
	void* _material;
	struct Level _pyramid;
	char _initialized;
} BloomRenderer_t;
struct BloomFogEnvironment;
struct BloomFog;
struct BloomFogEnvironmentParams;
typedef struct __attribute__((__packed__)) BloomFogEnvironmentParams {
	char _unused_data_useless[0xC];

	float colorMultiplier;
	float attenuation;
	float offset;
} BloomFogEnvironmentParams_t;
typedef struct __attribute__((__packed__)) BloomFog {
	char _unused_data_useless[0xC];

	struct BloomFogEnvironmentParams* fog0Params;
	struct BloomFogEnvironmentParams* fog1Params;
	char _bloomFogEnabled;
	float _transition;
} BloomFog_t;
typedef struct __attribute__((__packed__)) BloomFogEnvironment {
	char _unused_data_useless[0xC];

	struct BloomFog* _bloomFog;
	struct BloomFogEnvironmentParams* _fog0Params;
	struct BloomFogEnvironmentParams* _fog1Params;
} BloomFogEnvironment_t;
struct BloomPrePass;
struct BloomPrePassParams;
enum KernelSize {
	KernelSize_Kernel7,
	KernelSize_Kernel15,
	KernelSize_Kernel23,
	KernelSize_Kernel35,
	KernelSize_Kernel63,
	KernelSize_Kernel127,
	KernelSize_Kernel135,
	KernelSize_Kernel143
};
struct Vector2;
typedef struct __attribute__((__packed__)) Vector2 {
	float x;
	float y;
} Vector2_t;
typedef struct __attribute__((__packed__)) BloomPrePassParams {
	char _unused_data_useless[0xC];

	enum KernelSize bloom1KernelSize;
	float bloom1Boost;
	enum KernelSize bloom2KernelSize;
	float bloom2Boost;
	float bloom2Alpha;
	int downsample;
	int textureWidth;
	int textureHeight;
	struct Vector2 fov;
	float linesWidth;
	float linesFogDensity;
	float lineIntensityMultiplier;
	float gammaCorrection;
	void* linesTexture;
} BloomPrePassParams_t;
typedef struct __attribute__((__packed__)) BloomPrePass {
	char _unused_data_useless[0xC];

	struct BloomPrePassRenderer* _bloomPrepassRenderer;
	struct BloomPrePassParams* _params;
	void* _bloomPrePassRenderTexture;
} BloomPrePass_t;
struct BloomPrePassBGLight;
struct Color;
typedef struct __attribute__((__packed__)) Color {
	float r;
	float g;
	float b;
	float a;
} Color_t;
typedef struct __attribute__((__packed__)) BloomPrePassBGLight {
	char _unused_data_useless[0x10];

	float _intensity;
	float _minAlpha;
	float _grayscaleFactor;
	struct Color _color;
} BloomPrePassBGLight_t;
struct BloomPrePassGraphicsSettingsPresets;
struct Preset;
typedef struct __attribute__((__packed__)) Preset {
	char _unused_data_useless[0xC];

	enum KernelSize bloom1KernelSize;
	float bloom1Boost;
	enum KernelSize bloom2KernelSize;
	float bloom2Boost;
	float bloom2Alpha;
	int downsample;
	int textureWidth;
	int textureHeight;
	float lineIntensityMultiplier;
} Preset_t;
typedef struct __attribute__((__packed__)) BloomPrePassGraphicsSettingsPresets {
	char _unused_data_useless[0xC];

	struct Preset* _presets;
} BloomPrePassGraphicsSettingsPresets_t;
struct BloomPrePassRenderer;
typedef struct __attribute__((__packed__)) BloomPrePassRenderer {
	char _unused_data_useless[0xC];

	struct KawaseBlurRenderer* _kawaseBlurRenderer;
	struct BloomFog* _bloomFog;
	void* _linesShader;
	void* _maxColorShader;
	void* _gammaCorrectionShader;
	void* _linesMaterial;
	void* _maxColorMaterial;
	void* _gammaCorrectionMaterial;
	void* _mesh;
	struct Vector3 _vertices;
	struct Color _colors;
	struct Vector4 _viewPos;
	void* _commandBuffer;
} BloomPrePassRenderer_t;
struct Parametric3SliceSpriteController;
typedef struct __attribute__((__packed__)) Parametric3SliceSpriteController {
	char _unused_data_useless[0xC];

	float _widthMultiplier;
	float width;
	float length;
	float center;
	struct Color color;
	float alphaMultiplier;
	float minAlpha;
	void* _meshRenderer;
	void* _meshFilter;
	char _isInitialized;
} Parametric3SliceSpriteController_t;
struct ParametricBoxController;
typedef struct __attribute__((__packed__)) ParametricBoxController {
	char _unused_data_useless[0xC];

	float width;
	float height;
	float length;
	float heightCenter;
	struct Color color;
	float alphaMultiplier;
	float minAlpha;
	void* _meshRenderer;
} ParametricBoxController_t;
struct ParametricBoxFakeGlowController;
typedef struct __attribute__((__packed__)) ParametricBoxFakeGlowController {
	char _unused_data_useless[0xC];

	float width;
	float height;
	float length;
	float edgeSize;
	float edgeSizeMultiplier;
	struct Color color;
	void* _meshRenderer;
	struct MaterialPropertyBlockController* _materialPropertyBlockController;
} ParametricBoxFakeGlowController_t;
struct ParametricBoxFrameController;
typedef struct __attribute__((__packed__)) ParametricBoxFrameController {
	char _unused_data_useless[0xC];

	float width;
	float height;
	float length;
	float edgeSize;
	struct Color color;
	void* _meshRenderer;
	struct MaterialPropertyBlockController* _materialPropertyBlockController;
} ParametricBoxFrameController_t;
struct TubeBloomPrePassLight;
typedef struct __attribute__((__packed__)) TubeBloomPrePassLight {
	char _unused_data_useless[0x14];

	void* _mainEffectPostProcessEnabled;
	float _width;
	float _length;
	float _center;
	struct Color _color;
	float _colorAlphaMultiplier;
	float _fakeBloomAlphaMultiplier;
	float _bloomFogIntensityMultiplier;
	float _minAlpha;
	struct ParametricBoxController* _parametricBoxController;
	struct Parametric3SliceSpriteController* _dynamic3SliceSprite;
	void* _transform;
} TubeBloomPrePassLight_t;
struct BlueNoiseDithering;
typedef struct __attribute__((__packed__)) BlueNoiseDithering {
	char _unused_data_useless[0xC];

	void* _noiseTexture;
	int _noiseParamsID;
	int _globalNoiseTextureID;
} BlueNoiseDithering_t;
struct BlueNoiseDitheringUpdater;
struct RandomValueToShader;
typedef struct __attribute__((__packed__)) RandomValueToShader {
	char _unused_data_useless[0xC];

	int _lastFrameNum;
} RandomValueToShader_t;
typedef struct __attribute__((__packed__)) BlueNoiseDitheringUpdater {
	char _unused_data_useless[0xC];

	struct BlueNoiseDithering* _blueNoiseDithering;
	struct RandomValueToShader* _randomValueToShader;
} BlueNoiseDitheringUpdater_t;
struct BSLight;
typedef struct __attribute__((__packed__)) BSLight {
	char _unused_data_useless[0xC];

	int _ID;
} BSLight_t;
struct InstancingValuesTester;
struct PropertyNameFloatValuePair;
typedef struct __attribute__((__packed__)) PropertyNameFloatValuePair {
	char _unused_data_useless[0x8];

	cs_string* propertyName;
	float value;
} PropertyNameFloatValuePair_t;
struct PropertyNameVectorValuePair;
typedef struct __attribute__((__packed__)) PropertyNameVectorValuePair {
	char _unused_data_useless[0x8];

	cs_string* propertyName;
	struct Vector4 vector;
} PropertyNameVectorValuePair_t;
struct PropertyNameColorValuePair;
typedef struct __attribute__((__packed__)) PropertyNameColorValuePair {
	char _unused_data_useless[0x8];

	cs_string* propertyName;
	struct Color color;
} PropertyNameColorValuePair_t;
typedef struct __attribute__((__packed__)) InstancingValuesTester {
	char _unused_data_useless[0xC];

	struct MaterialPropertyBlockController* _materialPropertyBlockController;
	struct PropertyNameFloatValuePair* _floats;
	struct PropertyNameVectorValuePair* _vectors;
	struct PropertyNameColorValuePair* _colors;
} InstancingValuesTester_t;
struct KawaseBlurPostProcess;
typedef struct __attribute__((__packed__)) KawaseBlurPostProcess {
	char _unused_data_useless[0xC];

	struct KawaseBlurRenderer* _kawaseBlurRenderer;
	enum KernelSize _kernelSize;
	int _downsample;
} KawaseBlurPostProcess_t;
struct KawaseBlurRenderer;
struct BloomKernel;
typedef struct __attribute__((__packed__)) BloomKernel {
	char _unused_data_useless[0x8];

	enum KernelSize kernelSize;
	int sharedPart;
} BloomKernel_t;
typedef struct __attribute__((__packed__)) KawaseBlurRenderer {
	char _unused_data_useless[0xC];

	void* _kawaseBlurShader;
	void* _additiveShader;
	void* _kawaseBlurMaterial;
	void* _additiveMaterial;
	void* _commandBuffersMaterial;
	void* _kernels;
	struct BloomKernel* _bloomKernels;
} KawaseBlurRenderer_t;
struct LineLight;
typedef struct __attribute__((__packed__)) LineLight {
	char _unused_data_useless[0xC];

	struct Vector3 _p0;
	struct Vector3 _p1;
	struct Color _color;
} LineLight_t;
struct XWeaponTrailRenderer;
typedef struct __attribute__((__packed__)) XWeaponTrailRenderer {
	char _unused_data_useless[0xC];

	void* _meshRenderer;
	void* _meshFilter;
	void* _mesh;
} XWeaponTrailRenderer_t;
struct DirectionalESMLight;
typedef struct __attribute__((__packed__)) DirectionalESMLight {
	char _unused_data_useless[0xC];

	float _blurSize;
	void* _esmShadowTexture;
	void* _copyBuffer;
	void* _esmBlitMaterial;
} DirectionalESMLight_t;
struct EnableDepthTextureMode;
typedef struct __attribute__((__packed__)) EnableDepthTextureMode {
	char _unused_data_useless[0xC];

	enum DepthTextureMode _depthTextureMode;
} EnableDepthTextureMode_t;
struct MissionProgressTesting;
typedef struct __attribute__((__packed__)) MissionProgressTesting {
	char _unused_data_useless[0xC];

	cs_string* missionId;
	char cleared;
	char all;
	struct CampaignProgressModelSO* _missionsProgressModelSO;
} MissionProgressTesting_t;
struct OnRenderImageTest;
typedef struct __attribute__((__packed__)) OnRenderImageTest {
	char _unused_data_useless[0xC];

	void* _rt;
	void* _stereoCopyMaterial;
} OnRenderImageTest_t;
struct SaberActivityLineGraph;
typedef struct __attribute__((__packed__)) SaberActivityLineGraph {
	char _unused_data_useless[0xC];

	struct SaberActivityCounter* _saberActivityCounter;
	void* _lineRenderer;
	void* _lineRenderer2;
	int _pointCount;
	float _pointDistance;
	float _scale;
	float _updateFps;
	struct Vector3 _pointPositions;
	void* _pointsValues;
	void* _pointsValues2;
} SaberActivityLineGraph_t;
struct ScriptableObjectTestUser;
struct ScriptableObjectTest;
typedef struct __attribute__((__packed__)) ScriptableObjectTest {
	char _unused_data_useless[0xC];

	void* _someClass;
} ScriptableObjectTest_t;
typedef struct __attribute__((__packed__)) ScriptableObjectTestUser {
	char _unused_data_useless[0xC];

	struct ScriptableObjectTest* _scriptableObjectTest;
} ScriptableObjectTestUser_t;
struct SinMove;
typedef struct __attribute__((__packed__)) SinMove {
	char _unused_data_useless[0xC];

	float _speed;
	struct Vector3 _offset;
	float _time;
	struct Vector3 _startPos;
} SinMove_t;
struct SmoothFOV;
typedef struct __attribute__((__packed__)) SmoothFOV {
	char _unused_data_useless[0xC];

	void* _camera;
	float _smooth;
	float _fov;
} SmoothFOV_t;
struct TrackerInactivityChecker;
typedef struct __attribute__((__packed__)) TrackerInactivityChecker {
	char _unused_data_useless[0xC];

	void* _checkedTransform;
	float _maxAllowedPosOffset;
	float _maxAllowedRotOffset;
	float _minInactivityTime;
	void* _menuSceneSetupData;
	struct Vector3 _checkedPos;
	struct Vector3 _checkedRot;
	float _inactivityTime;
	char _inTransition;
} TrackerInactivityChecker_t;
struct AnalyticsManager;
typedef struct __attribute__((__packed__)) AnalyticsManager {
	char _unused_data_useless[0xC];

	void* _analyticsModel;
	void* _levelDidStartSignal;
	void* _levelDidFinishSignal;
	char _enabled;
} AnalyticsManager_t;
struct AudioClipQueue;
struct AudioSource;
struct AudioSourceExtension;
typedef struct __attribute__((__packed__)) AudioSourceExtension {
	char _unused_data_useless[0xC];

	struct AudioSource* m_audioSource;
	int m_ExtensionManagerUpdateIndex;
} AudioSourceExtension_t;
typedef struct __attribute__((__packed__)) AudioSource {
	char _unused_data_useless[0xC];

	struct AudioSourceExtension* spatializerExtension;
	struct AudioSourceExtension* ambisonicExtension;
} AudioSource_t;
typedef struct __attribute__((__packed__)) AudioClipQueue {
	char _unused_data_useless[0xC];

	struct AudioSource* _audioSource;
	void* _queue;
	float _delay;
} AudioClipQueue_t;
struct AudioFading;
typedef struct __attribute__((__packed__)) AudioFading {
	char _unused_data_useless[0xC];

	struct AudioSource* _audioSource;
	float _smooth;
	char _fadeInOnStart;
	float _targetVolume;
} AudioFading_t;
struct AudioPitchGainEffect;
typedef struct __attribute__((__packed__)) AudioPitchGainEffect {
	char _unused_data_useless[0xC];

	struct AudioSource* _audioSource;
	float _duration;
	void* _pitchCurve;
	void* _gainCurve;
} AudioPitchGainEffect_t;
struct AudioTimeSyncController;
typedef struct __attribute__((__packed__)) AudioTimeSyncController {
	char _unused_data_useless[0xC];

	float _audioSyncLerpSpeed;
	float _forcedSyncDeltaTime;
	float _startSyncDeltaTime;
	float _stopSyncDeltaTime;
	struct AudioSource* _audioSource;
	void* _audioLatency;
	char forcedAudioSync;
	float _songLength;
	char _fixingAudioSyncError;
	float _audioStartTimeOffsetSinceStart;
	int _playbackLoopIndex;
	int _prevAudioSamplePos;
	char _pause;
	float _startSongTime;
	float _songTimeOffset;
	char _audioStarted;
	float _timeScale;
	float _songTime;
	double _dspTimeOffset;
	void* didInitEvent;
	char didInit_k__BackingField;
} AudioTimeSyncController_t;
struct BombCutSoundEffect;
typedef struct __attribute__((__packed__)) BombCutSoundEffect {
	char _unused_data_useless[0xC];

	struct AudioSource* _audioSource;
	void* didFinishEvent;
	struct Saber* _saber;
} BombCutSoundEffect_t;
struct BombCutSoundEffectManager;
struct AudioClip;
typedef struct __attribute__((__packed__)) AudioClip {
	char _unused_data_useless[0xC];

	void* m_PCMReaderCallback;
	void* m_PCMSetPositionCallback;
} AudioClip_t;
typedef struct __attribute__((__packed__)) BombCutSoundEffectManager {
	char _unused_data_useless[0xC];

	float _volume;
	struct AudioClip* _bombExplosionAudioClips;
	struct BeatmapObjectSpawnController* _beatmapObjectSpawnController;
	struct PlayerController* _playerController;
	void* _bombCutSoundEffectPool;
	void* _randomSoundPicker;
} BombCutSoundEffectManager_t;
struct MainAudioEffects;
typedef struct __attribute__((__packed__)) MainAudioEffects {
	char _unused_data_useless[0xC];

	void* _audioLowPassFilter;
	float _smooth;
	float _targetFrequency;
} MainAudioEffects_t;
struct NoteCutSoundEffect;
typedef struct __attribute__((__packed__)) NoteCutSoundEffect {
	char _unused_data_useless[0xC];

	struct AudioSource* _audioSource;
	void* _speedToVolumeCurve;
	struct AudioClip* _badCutSoundEffectAudioClips;
	float _badCutVolume;
	float _goodCutVolume;
	void* didFinishEvent;
	char _isPlaying;
	struct Saber* _saber;
	struct NoteData* _noteData;
	float _volumeMultiplier;
	char _noteWasCut;
	float _aheadTime;
	float _timeToNextNote;
	float _timeToPrevNote;
	double _startDSPTime;
	double _endDSPtime;
	double _fadeOutStartDSPtime;
	float _noteMissedTimeOffset;
	float _beforeCutVolume;
	char _goodCut;
	void* _badCutRandomSoundPicker;
	char _handleWrongSaberTypeAsGood;
	char _paused;
	char _ignoreSaberSpeed;
} NoteCutSoundEffect_t;
struct NoteCutSoundEffectManager;
struct BeatmapObjectCallbackController;
struct BeatmapDataModel;
struct BeatmapData;
struct BeatmapLineData;
struct BeatmapObjectData;
enum BeatmapObjectType {
	BeatmapObjectType_Note,
	BeatmapObjectType_LongNote,
	BeatmapObjectType_Obstacle
};
typedef struct __attribute__((__packed__)) BeatmapObjectData {
	char _unused_data_useless[0x8];

	enum BeatmapObjectType beatmapObjectType_k__BackingField;
	float time_k__BackingField;
	int lineIndex_k__BackingField;
	int id_k__BackingField;
} BeatmapObjectData_t;
typedef struct __attribute__((__packed__)) BeatmapLineData {
	char _unused_data_useless[0x8];

	struct BeatmapObjectData* beatmapObjectsData;
} BeatmapLineData_t;
struct BeatmapEventData;
enum BeatmapEventType {
	BeatmapEventType_Event0,
	BeatmapEventType_Event1,
	BeatmapEventType_Event2,
	BeatmapEventType_Event3,
	BeatmapEventType_Event4,
	BeatmapEventType_Event5,
	BeatmapEventType_Event6,
	BeatmapEventType_Event7,
	BeatmapEventType_Event8,
	BeatmapEventType_Event9,
	BeatmapEventType_Event10,
	BeatmapEventType_Event11,
	BeatmapEventType_Event12,
	BeatmapEventType_Event13,
	BeatmapEventType_Event14,
	BeatmapEventType_Event15,
	BeatmapEventType_VoidEvent
};
typedef struct __attribute__((__packed__)) BeatmapEventData {
	char _unused_data_useless[0x8];

	enum BeatmapEventType type_k__BackingField;
	float time_k__BackingField;
	int value_k__BackingField;
} BeatmapEventData_t;
typedef struct __attribute__((__packed__)) BeatmapData {
	char _unused_data_useless[0x8];

	struct BeatmapLineData* beatmapLinesData_k__BackingField;
	struct BeatmapEventData* beatmapEventData_k__BackingField;
	int notesCount_k__BackingField;
	int obstaclesCount_k__BackingField;
	int bombsCount_k__BackingField;
	int spawnRotationEventsCount_k__BackingField;
} BeatmapData_t;
typedef struct __attribute__((__packed__)) BeatmapDataModel {
	char _unused_data_useless[0xC];

	void* beatmapDataDidChangeEvent;
	struct BeatmapData* _beatmapData;
} BeatmapDataModel_t;
typedef struct __attribute__((__packed__)) BeatmapObjectCallbackController {
	char _unused_data_useless[0xC];

	struct BeatmapDataModel* _beatmapDataModel;
	struct AudioTimeSyncController* _audioTimeSyncController;
	void* _beatmapObjectDataCallbackCacheList;
	void* beatmapEventDidTriggerEvent;
	void* _beatmapObjectCallbackData;
	void* _beatmapEarlyEventCallbackData;
	void* _beatmapLateEventCallbackData;
	int _nextEventIndex;
	float _startSongTime;
} BeatmapObjectCallbackController_t;
typedef struct __attribute__((__packed__)) NoteCutSoundEffectManager {
	char _unused_data_useless[0xC];

	struct Signal* _gameDidPauseSignal;
	struct Signal* _gameDidResumeSignal;
	struct AudioManagerSO* _audioManager;
	float _audioSamplesBeatAlignOffset;
	int _maxNumberOfEffects;
	struct AudioClip* _longCutEffectsAudioClips;
	struct AudioClip* _shortCutEffectsAudioClips;
	struct AudioClip* _testAudioClip;
	struct BeatmapObjectSpawnController* _beatmapObjectSpawnController;
	struct PlayerController* _playerController;
	struct BeatmapObjectCallbackController* _beatmapObjectCallbackController;
	void* _noteCutSoundEffectPool;
	struct AudioTimeSyncController* _audioTimeSyncController;
	char useTestAudioClip_k__BackingField;
	char handleWrongSaberTypeAsGood_k__BackingField;
	int _beatmapObjectCallbackId;
	void* _randomLongCutSoundPicker;
	void* _randomShortCutSoundPicker;
	float _prevNoteATime;
	float _prevNoteBTime;
	struct NoteCutSoundEffect* _prevNoteASoundEffect;
	struct NoteCutSoundEffect* _prevNoteBSoundEffect;
	float _beatAlignOffset;
} NoteCutSoundEffectManager_t;
struct ObstacleSaberSoundEffect;
enum SaberType {
	SaberType_SaberA,
	SaberType_SaberB
};
typedef struct __attribute__((__packed__)) ObstacleSaberSoundEffect {
	char _unused_data_useless[0xC];

	struct ObstacleSaberSparkleEffectManager* _obstacleSaberSparkleEffectManager;
	enum SaberType _saberType;
	struct AudioSource* _audioSource;
	float _volume;
	float _targetVolume;
} ObstacleSaberSoundEffect_t;
struct EventAudioBinding;
typedef struct __attribute__((__packed__)) EventAudioBinding {
	char _unused_data_useless[0x8];

	struct Signal* _signal;
	float _delay;
	struct AudioClip* _audioClips;
	struct AudioClipQueue* _audioClipQueue;
	void* _randomObjectPicker;
} EventAudioBinding_t;
struct SongPreviewPlayer;
typedef struct __attribute__((__packed__)) SongPreviewPlayer {
	char _unused_data_useless[0xC];

	int _channelsCount;
	struct AudioSource* _audioSourcePrefab;
	struct AudioClip* _defaultAudioClip;
	float _volume;
	float _ambientVolumeScale;
	float _defaultCrossfadeSpeed;
	float _defaultFadeOutSpeed;
	struct AudioSource* _audioSources;
	int _activeChannel;
	float _timeToDefaultAudioTransition;
	char _transitionAfterDelay;
	float _volumeScale;
	float _fadeSpeed;
} SongPreviewPlayer_t;
struct AchievementsModelSO;
typedef struct __attribute__((__packed__)) AchievementsModelSO {
	char _unused_data_useless[0xC];

	struct PlatformAchievementsModelSO* _platformAchievementsModel;
	void* _unlockedAchievementIds;
	char _initialized;
} AchievementsModelSO_t;
struct PlatformAchievementsModelSO;
typedef struct __attribute__((__packed__)) PlatformAchievementsModelSO {
	char _unused_data_useless[0xC];

	struct PS4AchievementIdsModelSO* _ps4AchievementIdsModel;
	void* _platformAchievementsHandler;
} PlatformAchievementsModelSO_t;
struct AdditionalContentModelSO;
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
struct TestPlatformAdditionalContentHandler;
struct Entitlement;
enum EntitlementStatus {
	EntitlementStatus_Failed,
	EntitlementStatus_Owned,
	EntitlementStatus_NotOwned
};
typedef struct __attribute__((__packed__)) Entitlement {
	char _unused_data_useless[0x8];

	cs_string* id;
	enum EntitlementStatus status;
} Entitlement_t;
typedef struct __attribute__((__packed__)) TestPlatformAdditionalContentHandler {
	char _unused_data_useless[0xC];

	struct Entitlement* _levelsEntitlements;
	struct Entitlement* _levelPacksEntitlements;
	char _packBetterBuyThanLevel;
	void* didInvalidateDataEvent;
} TestPlatformAdditionalContentHandler_t;
struct BookmarksFoldersModel;
struct FileBrowserItem;
typedef struct __attribute__((__packed__)) FileBrowserItem {
	char _unused_data_useless[0x8];

	cs_string* displayName_k__BackingField;
	cs_string* fullPath_k__BackingField;
	char isDirectory_k__BackingField;
} FileBrowserItem_t;
typedef struct __attribute__((__packed__)) BookmarksFoldersModel {
	char _unused_data_useless[0xC];

	void* myFolders;
	struct FileBrowserItem* _bookmarksFolders;
} BookmarksFoldersModel_t;
struct CustomLevelLoaderSO;
typedef struct __attribute__((__packed__)) CustomLevelLoaderSO {
	char _unused_data_useless[0xC];

	void* _beatmapCharacteristicCollection;
	void* _defaultEnviromentSceneInfo;
	struct EnviromentSceneInfoColectionSO* _enviromentSceneInfoColection;
	struct CachedMediaAsyncLoaderSO* _cachedMediaAsyncLoaderSO;
	void* _defaultPackCoverTexture2D;
} CustomLevelLoaderSO_t;
struct GameplayModifierParamsSO;
typedef struct __attribute__((__packed__)) GameplayModifierParamsSO {
	char _unused_data_useless[0xC];

	cs_string* _modifierName;
	cs_string* _hintText;
	float _multiplier;
	void* _icon;
	struct GameplayModifierParamsSO* _mutuallyExclusives;
} GameplayModifierParamsSO_t;
struct GameplayModifiers;
enum EnergyType {
	EnergyType_Bar,
	EnergyType_Battery
};
enum EnabledObstacleType {
	EnabledObstacleType_All,
	EnabledObstacleType_FullHeightOnly,
	EnabledObstacleType_NoObstacles
};
enum SongSpeed {
	SongSpeed_Normal,
	SongSpeed_Faster,
	SongSpeed_Slower
};
typedef struct __attribute__((__packed__)) GameplayModifiers {
	char _unused_data_useless[0x8];

	enum EnergyType _energyType;
	char _noFail;
	char _demoNoFail;
	char _instaFail;
	char _failOnSaberClash;
	enum EnabledObstacleType _enabledObstacleType;
	char _demoNoObstacles;
	char _noBombs;
	char _fastNotes;
	char _strictAngles;
	char _disappearingArrows;
	char _ghostNotes;
	enum SongSpeed _songSpeed;
	char _noArrows;
} GameplayModifiers_t;
struct GameplayModifiersModelSO;
typedef struct __attribute__((__packed__)) GameplayModifiersModelSO {
	char _unused_data_useless[0xC];

	struct GameplayModifierParamsSO* _batteryEnergy;
	struct GameplayModifierParamsSO* _noFail;
	struct GameplayModifierParamsSO* _instaFail;
	struct GameplayModifierParamsSO* _noObstacles;
	struct GameplayModifierParamsSO* _noBombs;
	struct GameplayModifierParamsSO* _fastNotes;
	struct GameplayModifierParamsSO* _strictAngles;
	struct GameplayModifierParamsSO* _disappearingArrows;
	struct GameplayModifierParamsSO* _fasterSong;
	struct GameplayModifierParamsSO* _slowerSong;
	struct GameplayModifierParamsSO* _noArrows;
	struct GameplayModifierParamsSO* _ghostNotes;
	struct GameplayModifierParamsSO* _demoNoObstacles;
	struct GameplayModifierParamsSO* _demoNoFail;
} GameplayModifiersModelSO_t;
struct LocalLeaderboardsModel;
typedef struct __attribute__((__packed__)) LocalLeaderboardsModel {
	char _unused_data_useless[0xC];

	int _maxNumberOfScoresInLeaderboard;
	void* newScoreWasAddedToLeaderboardEvent;
	void* _lastScorePositions;
	cs_string* _lastScoreLeaderboardId;
	void* _leaderboardsData;
	void* _dailyLeaderboardsData;
} LocalLeaderboardsModel_t;
struct PlatformLeaderboardsModel;
struct PlatformUserModelSO;
typedef struct __attribute__((__packed__)) PlatformUserModelSO {
	char _unused_data_useless[0xC];

	void* _platformUserHandler;
} PlatformUserModelSO_t;
struct LeaderboardScoreUploader;
typedef struct __attribute__((__packed__)) LeaderboardScoreUploader {
	char _unused_data_useless[0xC];

	void* allScoresDidUploadEvent;
	void* _scoresToUpload;
	void* _scoresToUploadForCurrentPlayer;
	void* _uploadScoreCallback;
	cs_string* _playerId;
	char _uploading;
} LeaderboardScoreUploader_t;
struct HMAsyncRequest;
typedef struct __attribute__((__packed__)) HMAsyncRequest {
	char _unused_data_useless[0x10];

	char _cancelled;
	void* _cancelHander;
} HMAsyncRequest_t;
typedef struct __attribute__((__packed__)) PlatformLeaderboardsModel {
	char _unused_data_useless[0xC];

	struct GameplayModifiersModelSO* _gameplayModifiersModelSO;
	struct PS4LeaderboardIdsModelSO* _ps4LeaderboardIdsModel;
	struct PlatformUserModelSO* _platformUserModel;
	void* allScoresDidUploadEvent;
	void* _platformLeaderboardsHandler;
	struct LeaderboardScoreUploader* _scoreUploader;
	cs_string* _playerId;
	struct HMAsyncRequest* _getUserInfoAsyncRequest;
} PlatformLeaderboardsModel_t;
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
struct BeatmapDataSO;
typedef struct __attribute__((__packed__)) BeatmapDataSO {
	char _unused_data_useless[0xC];

	cs_string* _jsonData;
	void* _signatureBytes;
	void* _projectedData;
	struct BeatmapData* _beatmapData;
	float _beatsPerMinute;
	float _shuffle;
	float _shufflePeriod;
	char _hasRequiredDataForLoad;
} BeatmapDataSO_t;
struct BeatmapSaveData;
typedef struct __attribute__((__packed__)) BeatmapSaveData {
	char _unused_data_useless[0x8];

	cs_string* _version;
	void* _events;
	void* _notes;
	void* _obstacles;
} BeatmapSaveData_t;
struct EventData;
typedef struct __attribute__((__packed__)) EventData {
	char _unused_data_useless[0x8];

	float _time;
	enum BeatmapEventType _type;
	int _value;
} EventData_t;
struct NoteData;
enum NoteLineLayer {
	NoteLineLayer_Base,
	NoteLineLayer_Upper,
	NoteLineLayer_Top
};
enum NoteType {
	NoteType_NoteA,
	NoteType_NoteB,
	NoteType_GhostNote,
	NoteType_Bomb
};
enum NoteCutDirection {
	NoteCutDirection_Up,
	NoteCutDirection_Down,
	NoteCutDirection_Left,
	NoteCutDirection_Right,
	NoteCutDirection_UpLeft,
	NoteCutDirection_UpRight,
	NoteCutDirection_DownLeft,
	NoteCutDirection_DownRight,
	NoteCutDirection_Any,
	NoteCutDirection_None
};
typedef struct __attribute__((__packed__)) NoteData {
	char _unused_data_useless[0x8];

	float _time;
	int _lineIndex;
	enum NoteLineLayer _lineLayer;
	enum NoteType _type;
	enum NoteCutDirection _cutDirection;
} NoteData_t;
struct ObstacleData;
enum ObstacleType {
	ObstacleType_FullHeight,
	ObstacleType_Top
};
typedef struct __attribute__((__packed__)) ObstacleData {
	char _unused_data_useless[0x8];

	float _time;
	int _lineIndex;
	enum ObstacleType _type;
	float _duration;
	int _width;
} ObstacleData_t;
struct BeatmapLevelDataLoaderSO;
typedef struct __attribute__((__packed__)) BeatmapLevelDataLoaderSO {
	char _unused_data_useless[0xC];

	void* _allBeatmapCharacteristicCollection;
	void* _beatmapLevelsAsyncCache;
	void* _bundleLevelInfos;
} BeatmapLevelDataLoaderSO_t;
struct BeatmapLevelCollectionSO;
typedef struct __attribute__((__packed__)) BeatmapLevelCollectionSO {
	char _unused_data_useless[0xC];

	struct BeatmapLevelSO* _beatmapLevels;
} BeatmapLevelCollectionSO_t;
struct BeatmapLevelDataSO;
typedef struct __attribute__((__packed__)) BeatmapLevelDataSO {
	char _unused_data_useless[0xC];

	struct AudioClip* _audioClip;
	struct DifficultyBeatmapSet* _difficultyBeatmapSets;
} BeatmapLevelDataSO_t;
struct DifficultyBeatmapSet;
typedef struct __attribute__((__packed__)) DifficultyBeatmapSet {
	char _unused_data_useless[0x8];

	cs_string* _beatmapCharacteristicSerializedName;
	struct DifficultyBeatmap* _difficultyBeatmaps;
} DifficultyBeatmapSet_t;
struct BeatmapLevelPackCollectionSO;
typedef struct __attribute__((__packed__)) BeatmapLevelPackCollectionSO {
	char _unused_data_useless[0xC];

	struct BeatmapLevelPackSO* _beatmapLevelPacks;
	struct PreviewBeatmapLevelPackSO* _previewBeatmapLevelPack;
	void* _allBeatmapLevelPacks;
} BeatmapLevelPackCollectionSO_t;
struct BeatmapLevelPackSO;
typedef struct __attribute__((__packed__)) BeatmapLevelPackSO {
	char _unused_data_useless[0xC];

	cs_string* _packID;
	cs_string* _packName;
	void* _coverImage;
	struct BeatmapLevelCollectionSO* _beatmapLevelCollection;
} BeatmapLevelPackSO_t;
struct BeatmapLevelsModelSO;
struct BeatmapLevelLoader;
typedef struct __attribute__((__packed__)) BeatmapLevelLoader {
	char _unused_data_useless[0x8];

	struct BeatmapLevelDataLoaderSO* _beatmapLevelDataLoader;
	void* _beatmapDataAssetFileModel;
} BeatmapLevelLoader_t;
typedef struct __attribute__((__packed__)) BeatmapLevelsModelSO {
	char _unused_data_useless[0xC];

	struct BeatmapLevelPackCollectionSO* _loadedBeatmapLevelPackCollection;
	struct BeatmapLevelDataLoaderSO* _beatmapLevelDataLoader;
	struct AdditionalContentModelSO* _additionalContentModel;
	int _maxCachedBeatmapLevels;
	struct CustomLevelLoaderSO* _customLevelLoader;
	struct SteamLevelProductsModelSO* _steamLevelProductsModel;
	struct OculusLevelProductsModelSO* _oculusLevelProductsModel;
	void* levelDownloadingUpdateEvent;
	void* _allLoadedBeatmapLevelPackCollection;
	void* _loadedBeatmapLevels;
	void* _loadedPreviewBeatmapLevels;
	struct BeatmapLevelLoader* _beatmapLevelLoader;
	void* _beatmapDataAssetFileModel;
	void* _loadAllOwnedPreviewLevelsCancellationTokenSource;
} BeatmapLevelsModelSO_t;
struct BeatmapLevelSO;
struct GetBeatmapLevelDataResult;
enum Result {
	Result_OK,
	Result_NotOwned,
	Result_Fail
};
typedef struct __attribute__((__packed__)) GetBeatmapLevelDataResult {
	enum Result _result;
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
struct DifficultyBeatmap;
enum BeatmapDifficulty {
	BeatmapDifficulty_Easy,
	BeatmapDifficulty_Normal,
	BeatmapDifficulty_Hard,
	BeatmapDifficulty_Expert,
	BeatmapDifficulty_ExpertPlus
};
typedef struct __attribute__((__packed__)) DifficultyBeatmap {
	char _unused_data_useless[0x8];

	enum BeatmapDifficulty _difficulty;
	int _difficultyRank;
	float _noteJumpMovementSpeed;
	float _noteJumpStartBeatOffset;
	struct BeatmapDataSO* _beatmapData;
	void* _parentLevel;
	void* _parentDifficultyBeatmapSet;
} DifficultyBeatmap_t;
struct PreviewBeatmapLevelPackSO;
typedef struct __attribute__((__packed__)) PreviewBeatmapLevelPackSO {
	char _unused_data_useless[0xC];

	cs_string* _packID;
	cs_string* _packName;
	void* _coverImage;
	void* _previewBeatmapLevelCollection;
} PreviewBeatmapLevelPackSO_t;
struct PreviewBeatmapLevelSO;
typedef struct __attribute__((__packed__)) PreviewBeatmapLevelSO {
	char _unused_data_useless[0xC];

	cs_string* _levelID;
	cs_string* _songName;
	cs_string* _songSubName;
	cs_string* _songAuthorName;
	cs_string* _levelAuthorName;
	struct AudioClip* _previewAudioClip;
	float _beatsPerMinute;
	float _songTimeOffset;
	float _shuffle;
	float _shufflePeriod;
	float _previewStartTime;
	float _previewDuration;
	float _songDuration;
	void* _coverImageTexture2D;
	void* _environmentSceneInfo;
	struct BeatmapCharacteristicSO* _beatmapCharacteristics;
} PreviewBeatmapLevelSO_t;
struct StandardLevelInfoSaveData;
typedef struct __attribute__((__packed__)) StandardLevelInfoSaveData {
	char _unused_data_useless[0x8];

	cs_string* _version;
	cs_string* _songName;
	cs_string* _songSubName;
	cs_string* _songAuthorName;
	cs_string* _levelAuthorName;
	float _beatsPerMinute;
	float _songTimeOffset;
	float _shuffle;
	float _shufflePeriod;
	float _previewStartTime;
	float _previewDuration;
	cs_string* _songFilename;
	cs_string* _coverImageFilename;
	cs_string* _environmentName;
	void* _difficultyBeatmapSets;
} StandardLevelInfoSaveData_t;
struct VersionCheck;
typedef struct __attribute__((__packed__)) VersionCheck {
	char _unused_data_useless[0x8];

	cs_string* _version;
} VersionCheck_t;
struct StandardLevelInfoSaveData_V100;
typedef struct __attribute__((__packed__)) StandardLevelInfoSaveData_V100 {
	char _unused_data_useless[0x8];

	cs_string* _version;
	cs_string* _songName;
	cs_string* _songSubName;
	cs_string* _songAuthorName;
	cs_string* _levelAuthorName;
	float _beatsPerMinute;
	float _songTimeOffset;
	float _shuffle;
	float _shufflePeriod;
	float _previewStartTime;
	float _previewDuration;
	cs_string* _songFilename;
	cs_string* _coverImageFilename;
	cs_string* _environmentName;
	struct DifficultyBeatmap* _difficultyBeatmaps;
} StandardLevelInfoSaveData_V100_t;
struct CampaignProgressModelSO;
typedef struct __attribute__((__packed__)) CampaignProgressModelSO {
	char _unused_data_useless[0xC];

	struct PlayerDataModelSO* _playerDataModelSO;
	void* _missionIds;
	cs_string* _finalMissionId;
	char _numberOfClearedMissionsDirty;
	int _numberOfClearedMissions;
} CampaignProgressModelSO_t;
struct MissionDataSO;
typedef struct __attribute__((__packed__)) MissionDataSO {
	char _unused_data_useless[0xC];

	struct BeatmapLevelSO* _level;
	struct BeatmapCharacteristicSO* _beatmapCharacteristic;
	enum BeatmapDifficulty _beatmapDifficulty;
	struct MissionObjective* _missionObjectives;
	struct GameplayModifiers* _gameplayModifiers;
	struct MissionHelpSO* _missionHelp;
} MissionDataSO_t;
struct MissionHelpSO;
typedef struct __attribute__((__packed__)) MissionHelpSO {
	char _unused_data_useless[0xC];

	cs_string* _missionHelpId;
} MissionHelpSO_t;
struct MissionNode;
typedef struct __attribute__((__packed__)) MissionNode {
	char _unused_data_useless[0xC];

	struct MissionDataSO* _missionDataSO;
	cs_string* _letterPartName;
	int _numberPartName;
	void* _rectTransform;
	struct MissionNodeVisualController* _missionNodeVisualController;
	struct MissionNode* _childNodes;
} MissionNode_t;
struct MissionNodeConnection;
typedef struct __attribute__((__packed__)) MissionNodeConnection {
	char _unused_data_useless[0xC];

	float _separator;
	float _width;
	void* _rectTransform;
	struct Image* _image;
	struct MissionNodeVisualController* _parentMissionNode;
	struct MissionNodeVisualController* _childMissionNode;
	void* _animator;
	struct Vector2 _parentMissionNodePosition;
	struct Vector2 _childMissionNodePosition;
	char _isActive;
} MissionNodeConnection_t;
struct MissionNodeNameGenerator;
typedef struct __attribute__((__packed__)) MissionNodeNameGenerator {
	char _unused_data_useless[0xC];

	struct MissionNodesManager* _missionNodesManager;
} MissionNodeNameGenerator_t;
struct MissionNodeSelectionManager;
typedef struct __attribute__((__packed__)) MissionNodeSelectionManager {
	char _unused_data_useless[0xC];

	struct MissionNodesManager* _missionNodesManager;
	void* didSelectMissionNodeEvent;
	struct MissionNode* _missionNodes;
	struct MissionNodeVisualController* _selectedNode;
} MissionNodeSelectionManager_t;
struct MissionNodesManager;
typedef struct __attribute__((__packed__)) MissionNodesManager {
	char _unused_data_useless[0xC];

	struct MissionNode* _rootMissionNode;
	struct MissionNode* _finalMissionNode;
	struct MissionStagesManager* _missionStagesManager;
	struct CampaignProgressModelSO* _missionProgressModel;
	void* _connectionsParentObject;
	void* _missionNodesParentObject;
	struct MissionNodeConnection* _allMissionNodeConnections;
	struct MissionNode* _allMissionNodes;
	char _isInitialized;
} MissionNodesManager_t;
struct MissionNodeUpdatePositionInEditMode;
typedef struct __attribute__((__packed__)) MissionNodeUpdatePositionInEditMode {
	char _unused_data_useless[0xC];

	struct MissionNodeConnection* _missionNodeConnection;
} MissionNodeUpdatePositionInEditMode_t;
struct MissionObjective;
enum ReferenceValueComparisonType {
	ReferenceValueComparisonType_None,
	ReferenceValueComparisonType_Equal,
	ReferenceValueComparisonType_Max,
	ReferenceValueComparisonType_Min
};
typedef struct __attribute__((__packed__)) MissionObjective {
	char _unused_data_useless[0x8];

	struct MissionObjectiveTypeSO* _type;
	enum ReferenceValueComparisonType _referenceValueComparisonType;
	int _referenceValue;
} MissionObjective_t;
struct MissionObjectiveTypeSO;
typedef struct __attribute__((__packed__)) MissionObjectiveTypeSO {
	char _unused_data_useless[0xC];

	cs_string* _objectiveName;
	char _noConditionValue;
	void* _objectiveValueFormater;
} MissionObjectiveTypeSO_t;
struct MissionStage;
typedef struct __attribute__((__packed__)) MissionStage {
	char _unused_data_useless[0xC];

	int _minimumMissionsToUnlock;
	void* _rectTransform;
} MissionStage_t;
struct MissionStagesManager;
typedef struct __attribute__((__packed__)) MissionStagesManager {
	char _unused_data_useless[0xC];

	struct MissionStageLockView* _missionStageLockView;
	struct MissionStage* _missionStages;
	struct MissionStage* _firstLockedMissionStage;
} MissionStagesManager_t;
struct PlayerDataModelSO;
struct LocalPlayer;
struct PlayerAllOverallStatsData;
struct PlayerOverallStatsData;
typedef struct __attribute__((__packed__)) PlayerOverallStatsData {
	char _unused_data_useless[0x8];

	int goodCutsCount_k__BackingField;
	int badCutsCount_k__BackingField;
	int missedCutsCount_k__BackingField;
	long totalScore_k__BackingField;
	int playedLevelsCount_k__BackingField;
	int cleardLevelsCount_k__BackingField;
	int failedLevelsCount_k__BackingField;
	int fullComboCount_k__BackingField;
	float timePlayed_k__BackingField;
	int handDistanceTravelled_k__BackingField;
	long cummulativeCutScoreWithoutMultiplier_k__BackingField;
} PlayerOverallStatsData_t;
typedef struct __attribute__((__packed__)) PlayerAllOverallStatsData {
	char _unused_data_useless[0x8];

	struct PlayerOverallStatsData* campaignOverallStatsData_k__BackingField;
	struct PlayerOverallStatsData* soloFreePlayOverallStatsData_k__BackingField;
	struct PlayerOverallStatsData* partyFreePlayOverallStatsData_k__BackingField;
} PlayerAllOverallStatsData_t;
typedef struct __attribute__((__packed__)) LocalPlayer {
	char _unused_data_useless[0x8];

	cs_string* playerId_k__BackingField;
	cs_string* playerName_k__BackingField;
	char shouldShowTutorialPrompt_k__BackingField;
	char agreedToEula_k__BackingField;
	struct GameplayModifiers* gameplayModifiers_k__BackingField;
	struct PlayerSpecificSettings* playerSpecificSettings_k__BackingField;
	struct PlayerAllOverallStatsData* playerAllOverallStatsData_k__BackingField;
	void* levelsStatsData_k__BackingField;
	void* missionsStatsData_k__BackingField;
	void* showedMissionHelpIds_k__BackingField;
} LocalPlayer_t;
typedef struct __attribute__((__packed__)) PlayerDataModelSO {
	char _unused_data_useless[0xC];

	void* _beatmapCharacteristicCollection;
	void* _localPlayers;
	void* _guestPlayers;
	struct LocalPlayer* _currentLocalPlayer;
	struct GameplayModifiers* _sharedGameplayModifiers;
	struct PlayerSpecificSettings* _sharedPlayerSpecificSettings;
	struct PracticeSettings* _sharedPracticeSettings;
	enum BeatmapDifficulty _sharedLastSelectedBeatmapDifficulty;
} PlayerDataModelSO_t;
struct PlayerLevelStatsData;
enum Rank {
	Rank_E,
	Rank_D,
	Rank_C,
	Rank_B,
	Rank_A,
	Rank_S,
	Rank_SS,
	Rank_SSS
};
typedef struct __attribute__((__packed__)) PlayerLevelStatsData {
	char _unused_data_useless[0x8];

	int _highScore;
	int _maxCombo;
	char _fullCombo;
	enum Rank _maxRank;
	char _validScore;
	int _playCount;
	cs_string* _levelID;
	enum BeatmapDifficulty _difficulty;
	struct BeatmapCharacteristicSO* _beatmapCharacteristic;
} PlayerLevelStatsData_t;
struct PlayerSpecificSettings;
typedef struct __attribute__((__packed__)) PlayerSpecificSettings {
	char _unused_data_useless[0x8];

	char _staticLights;
	char _leftHanded;
	char _swapColors;
	float _playerHeight;
	char _disableSFX;
	char _reduceDebris;
	char _noTextsAndHuds;
	char _advancedHud;
	char _autoRestart;
} PlayerSpecificSettings_t;
struct PracticeSettings;
typedef struct __attribute__((__packed__)) PracticeSettings {
	char _unused_data_useless[0x8];

	float _startSongTime;
	float _songSpeedMul;
	char _startInAdvanceAndClearNotes;
} PracticeSettings_t;
struct BeatmapEditorSceneSetupData;
typedef struct __attribute__((__packed__)) BeatmapEditorSceneSetupData {
	char _unused_data_useless[0x8];

	cs_string* _levelDirPath;
	cs_string* _levelAssetPath;
} BeatmapEditorSceneSetupData_t;
struct GameplayCoreSceneSetupData;
typedef struct __attribute__((__packed__)) GameplayCoreSceneSetupData {
	char _unused_data_useless[0x8];

	void* _difficultyBeatmap;
	struct GameplayModifiers* _gameplayModifiers;
	struct PlayerSpecificSettings* _playerSpecificSettings;
	struct PracticeSettings* _practiceSettings;
	char _useTestNoteCutSoundEffects;
} GameplayCoreSceneSetupData_t;
struct HealthWarningSceneSetupData;
struct ScenesTransitionSetupDataSO;
struct SceneInfoSceneSetupDataPair;
typedef struct __attribute__((__packed__)) SceneInfoSceneSetupDataPair {
	char _unused_data_useless[0x8];

	void* sceneInfo_k__BackingField;
	void* data_k__BackingField;
} SceneInfoSceneSetupDataPair_t;
typedef struct __attribute__((__packed__)) ScenesTransitionSetupDataSO {
	char _unused_data_useless[0xC];

	struct SceneInfoSceneSetupDataPair* _sceneInfoSceneSetupDataPairs;
} ScenesTransitionSetupDataSO_t;
typedef struct __attribute__((__packed__)) HealthWarningSceneSetupData {
	char _unused_data_useless[0x8];

	struct ScenesTransitionSetupDataSO* _nextScenesTransitionSetupData;
} HealthWarningSceneSetupData_t;
struct MissionGameplaySceneSetupData;
typedef struct __attribute__((__packed__)) MissionGameplaySceneSetupData {
	char _unused_data_useless[0x8];

	struct MissionObjective* _missionObjectives;
	struct PlayerSpecificSettings* _playerSpecificSettings;
} MissionGameplaySceneSetupData_t;
struct MenuScenesTransitionSetupDataSO;
typedef struct __attribute__((__packed__)) MenuScenesTransitionSetupDataSO {
	char _unused_data_useless[0x10];

	void* _menuSceneInfo;
	void* _menuCoreSceneInfo;
	void* _menuEnvironmentSceneInfo;
	void* _menuViewControllersSceneInfo;
} MenuScenesTransitionSetupDataSO_t;
struct MenuTransitionsHelperSO;
struct TutorialScenesTransitionSetupDataSO;
typedef struct __attribute__((__packed__)) TutorialScenesTransitionSetupDataSO {
	char _unused_data_useless[0x14];

	void* didFinishEvent;
} TutorialScenesTransitionSetupDataSO_t;
struct CreditsScenesTransitionSetupDataSO;
typedef struct __attribute__((__packed__)) CreditsScenesTransitionSetupDataSO {
	char _unused_data_useless[0x14];

	void* didFinishEvent;
} CreditsScenesTransitionSetupDataSO_t;
struct BeatmapEditorScenesTransitionSetupDataSO;
typedef struct __attribute__((__packed__)) BeatmapEditorScenesTransitionSetupDataSO {
	char _unused_data_useless[0x14];

	void* didFinishEvent;
} BeatmapEditorScenesTransitionSetupDataSO_t;
typedef struct __attribute__((__packed__)) MenuTransitionsHelperSO {
	char _unused_data_useless[0xC];

	void* _initSceneSetupData;
	struct StandardLevelScenesTransitionSetupDataSO* _standardLevelScenesTransitionSetupData;
	struct MissionLevelScenesTransitionSetupDataSO* _missionLevelSceneTransitionSetupData;
	struct TutorialScenesTransitionSetupDataSO* _tutorialSceneTransitionSetupData;
	struct CreditsScenesTransitionSetupDataSO* _creditsSceneTransitionSetupData;
	struct BeatmapEditorScenesTransitionSetupDataSO* _beatmapEditorSceneTransitionSetupData;
	void* _levelDidStartSignal;
	void* _levelDidFinishSignal;
	void* _standardLevelFinishedCallback;
	void* _missionLevelFinishedCallback;
	void* _beatmapEditorFinishedCallback;
	void* _difficultyBeatmap;
} MenuTransitionsHelperSO_t;
struct MissionLevelScenesTransitionSetupDataSO;
typedef struct __attribute__((__packed__)) MissionLevelScenesTransitionSetupDataSO {
	char _unused_data_useless[0x10];

	void* _missionGameplaySceneInfo;
	void* _gameplayCoreSceneInfo;
	void* _gameCoreSceneInfo;
	void* didFinishEvent;
} MissionLevelScenesTransitionSetupDataSO_t;
struct StandardLevelScenesTransitionSetupDataSO;
typedef struct __attribute__((__packed__)) StandardLevelScenesTransitionSetupDataSO {
	char _unused_data_useless[0x10];

	void* _standardGameplaySceneInfo;
	void* _gameplayCoreSceneInfo;
	void* _gameCoreSceneInfo;
	void* didFinishEvent;
} StandardLevelScenesTransitionSetupDataSO_t;
struct StandardGameplaySceneSetupData;
typedef struct __attribute__((__packed__)) StandardGameplaySceneSetupData {
	char _unused_data_useless[0x8];

	struct PlayerSpecificSettings* _playerSpecificSettings;
	cs_string* _backButtonText;
} StandardGameplaySceneSetupData_t;
struct HealthWarningTestSceneSetupDataInstaller;
typedef struct __attribute__((__packed__)) HealthWarningTestSceneSetupDataInstaller {
	char _unused_data_useless[0xC];

	struct HealthWarningSceneSetupData* _healthWarningSceneSetupData;
	void* _healthWarningScenesTransitionSetupData;
} HealthWarningTestSceneSetupDataInstaller_t;
struct InitTestSceneSetupDataInstaller;
typedef struct __attribute__((__packed__)) InitTestSceneSetupDataInstaller {
	char _unused_data_useless[0xC];

	void* _initSceneSetupData;
	void* _initScenesTransitionSetupData;
} InitTestSceneSetupDataInstaller_t;
struct MissionLevelTestSceneSetupDataInstaller;
typedef struct __attribute__((__packed__)) MissionLevelTestSceneSetupDataInstaller {
	char _unused_data_useless[0xC];

	struct MissionLevelScenesTransitionSetupDataSO* _missionLevelSceneTransitionSetupData;
	struct BeatmapLevelSO* _defaultStandardLevel;
	enum BeatmapDifficulty _defaultDifficulty;
	struct BeatmapCharacteristicSO* _defaultCharacteristic;
	struct GameplayModifiers* _defaultGameplayModifiers;
	struct PlayerSpecificSettings* _defaultPlayerSpecificSettings;
	struct MissionObjective* _defaultMissionObjectives;
} MissionLevelTestSceneSetupDataInstaller_t;
struct StandardLevelTestSceneSetupDataInstaller;
typedef struct __attribute__((__packed__)) StandardLevelTestSceneSetupDataInstaller {
	char _unused_data_useless[0xC];

	struct BeatmapLevelSO* _defaultStandardLevel;
	struct BeatmapCharacteristicSO* _defaultBeatmapCharacteristic;
	enum BeatmapDifficulty _defaultDifficulty;
	struct GameplayModifiers* _defaultGameplayModifiers;
	struct PlayerSpecificSettings* _defaultPlayerSpecificSettings;
	char _usePracticeSettings;
	struct PracticeSettings* _practiceSettings;
	struct StandardLevelScenesTransitionSetupDataSO* _standardLevelScenesTransitionSetupData;
} StandardLevelTestSceneSetupDataInstaller_t;
struct BeatEffect;
typedef struct __attribute__((__packed__)) BeatEffect {
	char _unused_data_useless[0xC];

	void* didFinishEvent;
	void* _spriteRenderer;
	void* _spriteTransform;
	struct TubeBloomPrePassLight* _tubeBloomPrePassLight;
	void* _lightIntensityCurve;
	void* _spriteXScaleCurve;
	void* _spriteYScaleCurve;
	void* _transparencyCurve;
	float _animationDuration;
	float _elapsedTime;
	struct Color _color;
} BeatEffect_t;
struct BeatEffectSpawner;
struct SongController;
typedef struct __attribute__((__packed__)) SongController {
	char _unused_data_useless[0xC];

	void* songDidFinishEvent;
} SongController_t;
typedef struct __attribute__((__packed__)) BeatEffectSpawner {
	char _unused_data_useless[0xC];

	struct ColorManager* _colorManager;
	float _effectDuration;
	struct BeatmapObjectSpawnController* _beatmapObjectSpawnController;
	void* _beatEffectPool;
	struct SongController* _songController;
} BeatEffectSpawner_t;
struct BombExplosionEffect;
typedef struct __attribute__((__packed__)) BombExplosionEffect {
	char _unused_data_useless[0xC];

	void* _debrisPS;
	void* _explosionPS;
	int _debrisCount;
	int _explosionParticlesCount;
	void* _emitParams;
	void* _explosionPSEmitParams;
} BombExplosionEffect_t;
struct CutoutAnimateEffect;
typedef struct __attribute__((__packed__)) CutoutAnimateEffect {
	char _unused_data_useless[0xC];

	struct MaterialPropertyBlockController* _materialPropertyBlockControllers;
	void* _transitionCurve;
	char animating_k__BackingField;
	struct Vector3 _randomNoiseTexOffset;
} CutoutAnimateEffect_t;
struct EmitParticles;
typedef struct __attribute__((__packed__)) EmitParticles {
	char _unused_data_useless[0xC];

	void* _particleSystem;
} EmitParticles_t;
struct FogSwitchEventEffect;
typedef struct __attribute__((__packed__)) FogSwitchEventEffect {
	char _unused_data_useless[0xC];

	struct BloomFog* _bloomFog;
	enum BeatmapEventType _event;
	struct BeatmapObjectCallbackController* _beatmapObjectCallbackController;
} FogSwitchEventEffect_t;
struct LightPairRotationEventEffect;
struct RotationData;
struct Quaternion;
typedef struct __attribute__((__packed__)) Quaternion {
	float x;
	float y;
	float z;
	float w;
} Quaternion_t;
typedef struct __attribute__((__packed__)) RotationData {
	char _unused_data_useless[0x8];

	char enabled;
	float rotationSpeed;
	struct Quaternion startRotation;
	void* transform;
} RotationData_t;
typedef struct __attribute__((__packed__)) LightPairRotationEventEffect {
	char _unused_data_useless[0xC];

	enum BeatmapEventType _eventL;
	enum BeatmapEventType _eventR;
	struct Vector3 _rotationVector;
	char _overrideRandomValues;
	float _startRotation;
	void* _transformL;
	void* _transformR;
	struct BeatmapObjectCallbackController* _beatmapObjectCallbackController;
	struct RotationData* _rotationDataL;
	struct RotationData* _rotationDataR;
	int _randomGenerationFrameNum;
	float _randomStartRotation;
	float _randomDirection;
} LightPairRotationEventEffect_t;
struct LightRotationEventEffect;
typedef struct __attribute__((__packed__)) LightRotationEventEffect {
	char _unused_data_useless[0xC];

	enum BeatmapEventType _event;
	struct Vector3 _rotationVector;
	struct BeatmapObjectCallbackController* _beatmapObjectCallbackController;
	void* _transform;
	struct Quaternion _startRotation;
	float _rotationSpeed;
} LightRotationEventEffect_t;
struct LightSwitchEventEffect;
typedef struct __attribute__((__packed__)) LightSwitchEventEffect {
	char _unused_data_useless[0xC];

	void* _lightColor0;
	void* _lightColor1;
	void* _highlightColor0;
	void* _highlightColor1;
	char _lightOnStart;
	int _lightsID;
	enum BeatmapEventType _event;
	struct BeatmapObjectCallbackController* _beatmapObjectCallbackController;
	char _lightIsOn;
	struct Color _offColor;
	float _highlightValue;
	struct Color _afterHighlightColor;
	struct Color _highlightColor;
	float kFadeSpeed;
	struct BSLight* _lights;
	char _didProcessFirstEvent;
} LightSwitchEventEffect_t;
struct TunnelSmokeEventEffect;
typedef struct __attribute__((__packed__)) TunnelSmokeEventEffect {
	char _unused_data_useless[0xC];

	enum BeatmapEventType _event;
	void* _particleSystem;
	struct BeatmapObjectCallbackController* _beatmapObjectCallbackController;
	void* _mainModule;
	void* _shapeModule;
	void* _particles;
} TunnelSmokeEventEffect_t;
struct FireworkItemController;
typedef struct __attribute__((__packed__)) FireworkItemController {
	char _unused_data_useless[0xC];

	struct TubeBloomPrePassLight* _lights;
	void* _particleSystem;
	struct AudioSource* _audioSource;
	int _numberOfParticles;
	float _lightFlashDuration;
	void* _lightIntensityCurve;
	struct Color _lightsColor;
	struct AudioClip* _explosionClips;
	void* _randomAudioPicker;
	void* didFinishEvent;
} FireworkItemController_t;
struct FireworksController;
typedef struct __attribute__((__packed__)) FireworksController {
	char _unused_data_useless[0xC];

	struct Vector3 _spawnSize;
	float _minSpawnInterval;
	float _maxSpawnInterval;
	void* _fireworkItemPool;
} FireworksController_t;
struct FlyingObjectEffect;
typedef struct __attribute__((__packed__)) FlyingObjectEffect {
	char _unused_data_useless[0xC];

	void* _moveAnimationCurve;
	float _shakeFrequency;
	float _shakeStrength;
	void* _shakeStrengthAnimationCurve;
	void* didFinishEvent;
	char _initialized;
	struct Quaternion _rotation;
	float _elapsedTime;
	struct Vector3 _startPos;
	struct Vector3 _targetPos;
	float _duration;
	char _shake;
} FlyingObjectEffect_t;
struct FlyingScoreEffect;
struct TextMeshPro;
struct Bounds;
typedef struct __attribute__((__packed__)) Bounds {
	struct Vector3 m_Center;
	struct Vector3 m_Extents;
} Bounds_t;
struct TMP_SubMesh;
typedef struct __attribute__((__packed__)) TMP_SubMesh {
	char _unused_data_useless[0xC];

	struct TMP_FontAsset* m_fontAsset;
	struct TMP_SpriteAsset* m_spriteAsset;
	void* m_material;
	void* m_sharedMaterial;
	void* m_fallbackMaterial;
	void* m_fallbackSourceMaterial;
	char m_isDefaultMaterial;
	float m_padding;
	void* m_renderer;
	void* m_meshFilter;
	void* m_mesh;
	struct TextMeshPro* m_TextComponent;
	char m_isRegisteredForEvents;
} TMP_SubMesh_t;
enum MaskingTypes {
	MaskingTypes_MaskOff,
	MaskingTypes_MaskHard,
	MaskingTypes_MaskSoft
};
typedef struct __attribute__((__packed__)) TextMeshPro {
	char _unused_data_useless[0x86C];

	char m_currentAutoSizeMode;
	char m_hasFontAssetChanged;
	float m_previousLossyScaleY;
	void* m_renderer;
	void* m_meshFilter;
	char m_isFirstAllocation;
	int m_max_characters;
	int m_max_numberOfLines;
	struct Bounds m_default_bounds;
	struct TMP_SubMesh* m_subTextObjects;
	char m_isMaskingEnabled;
	char isMaskUpdateRequired;
	enum MaskingTypes m_maskType;
	struct Matrix4x4 m_EnvMapMatrix;
	struct Vector3 m_RectTransformCorners;
	char m_isRegisteredForEvents;
	int loopCountA;
} TextMeshPro_t;
struct NoteCutInfo;
struct SaberAfterCutSwingRatingCounter;
typedef struct __attribute__((__packed__)) SaberAfterCutSwingRatingCounter {
	char _unused_data_useless[0x10];

	void* didChangeEvent;
	void* didFinishEvent;
	struct Vector3 _cutPlaneNormal;
	float _cutTime;
	struct Vector3 _prevTopPos;
	struct Vector3 _prevBottomPos;
	float _rating;
	char _didFinish;
} SaberAfterCutSwingRatingCounter_t;
typedef struct __attribute__((__packed__)) NoteCutInfo {
	char _unused_data_useless[0x8];

	char speedOK_k__BackingField;
	char directionOK_k__BackingField;
	char saberTypeOK_k__BackingField;
	char wasCutTooSoon_k__BackingField;
	float saberSpeed_k__BackingField;
	struct Vector3 saberDir_k__BackingField;
	enum SaberType saberType_k__BackingField;
	float swingRating_k__BackingField;
	float timeDeviation_k__BackingField;
	float cutDirDeviation_k__BackingField;
	struct Vector3 cutPoint_k__BackingField;
	struct Vector3 cutNormal_k__BackingField;
	float cutDistanceToCenter_k__BackingField;
	struct SaberAfterCutSwingRatingCounter* afterCutSwingRatingCounter_k__BackingField;
} NoteCutInfo_t;
typedef struct __attribute__((__packed__)) FlyingScoreEffect {
	char _unused_data_useless[0x58];

	void* _fadeAnimationCurve;
	void* _maxCutDistanceScoreIndicator;
	struct TextMeshPro* _text;
	struct Color _color;
	float _colorAMultiplier;
	struct NoteCutInfo* _noteCutInfo;
	struct SaberAfterCutSwingRatingCounter* _saberAfterCutSwingRatingCounter;
} FlyingScoreEffect_t;
struct FlyingSpriteEffect;
typedef struct __attribute__((__packed__)) FlyingSpriteEffect {
	char _unused_data_useless[0x58];

	void* _spriteRenderer;
	void* _fadeAnimationCurve;
	struct Color _color;
} FlyingSpriteEffect_t;
struct FlyingSpriteSpawner;
typedef struct __attribute__((__packed__)) FlyingSpriteSpawner {
	char _unused_data_useless[0xC];

	void* _sprite;
	void* _material;
	float _duration;
	float _xSpread;
	float _targetYPos;
	float _targetZPos;
	struct Color _color;
	char _shake;
	void* _flyingSpriteEffectPool;
} FlyingSpriteSpawner_t;
struct FlyingTextEffect;
typedef struct __attribute__((__packed__)) FlyingTextEffect {
	char _unused_data_useless[0x58];

	struct TextMeshPro* _text;
	void* _fadeAnimationCurve;
	struct Color _color;
} FlyingTextEffect_t;
struct FlyingTextSpawner;
typedef struct __attribute__((__packed__)) FlyingTextSpawner {
	char _unused_data_useless[0xC];

	float _duration;
	float _xSpread;
	float _targetYPos;
	float _targetZPos;
	struct Color _color;
	float _fontSize;
	char _shake;
	void* _flyingTextEffectPool;
} FlyingTextSpawner_t;
struct HeadObstacleLowPassAudioEffect;
typedef struct __attribute__((__packed__)) HeadObstacleLowPassAudioEffect {
	char _unused_data_useless[0xC];

	struct PlayerHeadAndObstacleInteraction* _playerHeadAndObstacleInteraction;
	struct MainAudioEffects* _mainAudioEffects;
	char _headWasInObstacle;
} HeadObstacleLowPassAudioEffect_t;
struct EnvironmentLightSimpleController;
typedef struct __attribute__((__packed__)) EnvironmentLightSimpleController {
	char _unused_data_useless[0xC];

	struct Color _color;
	int _colorId;
	struct BSLight* _lights;
} EnvironmentLightSimpleController_t;
struct MenuLightsManager;
typedef struct __attribute__((__packed__)) MenuLightsManager {
	char _unused_data_useless[0xC];

	struct MenuLightsPresetSO* _defaultPreset;
	void* _playersPlaceNeonsMaterial;
	void* _menuScreensMaterial;
	float _smooth;
	void* _lights;
	struct MenuLightsPresetSO* _preset;
} MenuLightsManager_t;
struct MenuLightsPresetSO;
struct LightIdColorPair;
typedef struct __attribute__((__packed__)) LightIdColorPair {
	char _unused_data_useless[0x8];

	int lightId;
	void* baseColor;
	float intensity;
} LightIdColorPair_t;
typedef struct __attribute__((__packed__)) MenuLightsPresetSO {
	char _unused_data_useless[0xC];

	void* _playersPlaceNeonsColor;
	float _playersPlaceNeonsIntensity;
	void* _screensColor;
	struct Color _screensTintColor;
	struct LightIdColorPair* _lightIdColorPairs;
} MenuLightsPresetSO_t;
struct MenuShockwave;
typedef struct __attribute__((__packed__)) MenuShockwave {
	char _unused_data_useless[0xC];

	struct ShockwaveEffect* _shockwaveEffect;
	struct VRPointer* _vrPointer;
	struct Signal* _buttonClickEvents;
} MenuShockwave_t;
struct MissedNoteEffect;
typedef struct __attribute__((__packed__)) MissedNoteEffect {
	char _unused_data_useless[0xC];

	void* _songTime;
	void* _animationClip;
	void* _spriteRenderers;
	void* didFinishEvent;
	struct SongController* _songController;
	float _animationDuration;
	float _startAnimationTime;
} MissedNoteEffect_t;
struct MissedNoteEffectSpawner;
typedef struct __attribute__((__packed__)) MissedNoteEffectSpawner {
	char _unused_data_useless[0xC];

	struct FlyingSpriteSpawner* _missedNoteFlyingSpriteSpawner;
	struct BeatmapObjectSpawnController* _beatmapObjectSpawnController;
	float _spawnPosZ;
} MissedNoteEffectSpawner_t;
struct MissionClearedEnvironmentEffect;
typedef struct __attribute__((__packed__)) MissionClearedEnvironmentEffect {
	char _unused_data_useless[0xC];

	struct MissionObjectiveCheckersManager* _missionObjectiveCheckersManager;
	struct BeatmapObjectCallbackController* _beatmapObjectCallbackController;
} MissionClearedEnvironmentEffect_t;
struct NoteCutEffectSpawner;
struct NoteDebrisSpawner;
typedef struct __attribute__((__packed__)) NoteDebrisSpawner {
	char _unused_data_useless[0xC];

	char reduceDebris_k__BackingField;
	void* _noteDebrisPool;
} NoteDebrisSpawner_t;
struct NoteCutHapticEffect;
typedef struct __attribute__((__packed__)) NoteCutHapticEffect {
	char _unused_data_useless[0xC];

	struct HapticFeedbackController* _hapticFeedbackController;
} NoteCutHapticEffect_t;
struct FlyingScoreSpawner;
typedef struct __attribute__((__packed__)) FlyingScoreSpawner {
	char _unused_data_useless[0xC];

	void* _flyingScoreEffectPool;
	void* lineSlotSpawnTimes;
} FlyingScoreSpawner_t;
typedef struct __attribute__((__packed__)) NoteCutEffectSpawner {
	char _unused_data_useless[0xC];

	struct ColorManager* _colorManager;
	struct NoteCutParticlesEffect* _noteCutParticlesEffect;
	struct NoteDebrisSpawner* _noteDebrisSpawner;
	struct NoteCutHapticEffect* _noteCutHapticEffect;
	struct FlyingSpriteSpawner* _failFlyingSpriteSpawner;
	struct FlyingScoreSpawner* _flyingScoreSpawner;
	struct ShockwaveEffect* _shockwaveEffect;
	struct BombExplosionEffect* _bombExplosionEffect;
	struct BeatmapObjectSpawnController* _beatmapObjectSpawnController;
	struct ScoreController* _scoreController;
	char _spawnScores;
} NoteCutEffectSpawner_t;
struct NoteCutParticlesEffect;
typedef struct __attribute__((__packed__)) NoteCutParticlesEffect {
	char _unused_data_useless[0xC];

	void* _sparklesPS;
	void* _explosionPS;
	void* _explosionCorePS;
	void* _sparklesPSEmitParams;
	void* _sparklesPSMainModule;
	void* _sparklesPSShapeModule;
	void* _explosionPSEmitParams;
	void* _explosionCoresPSEmitParams;
	void* _sparklesLifetimeMinMaxCurve;
} NoteCutParticlesEffect_t;
struct NoteTrailEffect;
typedef struct __attribute__((__packed__)) NoteTrailEffect {
	char _unused_data_useless[0xC];

	int _particlesPerFrame;
	float _maxSpawnDistance;
	struct NoteMovement* _noteMovement;
	void* _noteTrailParticleSystem;
} NoteTrailEffect_t;
struct ObstacleSaberSparkleEffect;
typedef struct __attribute__((__packed__)) ObstacleSaberSparkleEffect {
	char _unused_data_useless[0xC];

	void* _sparkleParticleSystem;
	void* _burnParticleSystem;
	void* _sparkleParticleSystemEmmisionModule;
	void* _burnParticleSystemEmmisionModule;
} ObstacleSaberSparkleEffect_t;
struct ObstacleSaberSparkleEffectManager;
struct ActiveObstaclesManager;
typedef struct __attribute__((__packed__)) ActiveObstaclesManager {
	char _unused_data_useless[0xC];

	void* _activeObstacleControllers;
} ActiveObstaclesManager_t;
typedef struct __attribute__((__packed__)) ObstacleSaberSparkleEffectManager {
	char _unused_data_useless[0xC];

	struct ActiveObstaclesManager* _activeObstaclesManager;
	struct ObstacleSaberSparkleEffect* _obstacleSaberSparkleEffectPefab;
	struct PlayerController* _playerController;
	struct HapticFeedbackController* _hapticFeedbackController;
	void* sparkleEffectDidStartEvent;
	void* sparkleEffectDidEndEvent;
	struct Saber* _sabers;
	struct ObstacleSaberSparkleEffect* _effects;
	void* _effectsTransforms;
	void* _isSystemActive;
	void* _wasSystemActive;
	struct Vector3 _burnMarkPositions;
} ObstacleSaberSparkleEffectManager_t;
struct SaberClashEffect;
typedef struct __attribute__((__packed__)) SaberClashEffect {
	char _unused_data_useless[0xC];

	void* _sparkleParticleSystem;
	void* _glowParticleSystem;
	struct SaberClashChecker* _saberClashChecker;
	struct HapticFeedbackController* _hapticFeedbackController;
	void* _sparkleParticleSystemEmmisionModule;
	void* _glowParticleSystemEmmisionModule;
	char _sabersAreClashing;
} SaberClashEffect_t;
struct ShockwaveEffect;
typedef struct __attribute__((__packed__)) ShockwaveEffect {
	char _unused_data_useless[0xC];

	void* _shockwavePS;
	void* _shockwavePSEmitParams;
	void* _shockwaveParticles;
	float _prevShockwaveParticleSpawnTime;
} ShockwaveEffect_t;
struct EnvironmentSpawnRotation;
typedef struct __attribute__((__packed__)) EnvironmentSpawnRotation {
	char _unused_data_useless[0xC];

	float _aheadTime;
	float _smooth;
} EnvironmentSpawnRotation_t;
struct FlickeringNeonSign;
typedef struct __attribute__((__packed__)) FlickeringNeonSign {
	char _unused_data_useless[0xC];

	void* _flickeringSprite;
	struct TubeBloomPrePassLight* _light;
	float _minOnDelay;
	float _maxOnDelay;
	float _minOffDelay;
	float _maxOffDelay;
	struct Color _spriteOnColor;
	struct Color _lightOnColor;
	void* _onMaterial;
	void* _offMaterial;
} FlickeringNeonSign_t;
struct FlyingCar;
typedef struct __attribute__((__packed__)) FlyingCar {
	char _unused_data_useless[0xC];

	float _startZ;
	float _endZ;
	float _speed;
	float _progress;
	struct Vector3 _pos;
} FlyingCar_t;
struct BasicSpectrogramData;
typedef struct __attribute__((__packed__)) BasicSpectrogramData {
	char _unused_data_useless[0xC];

	struct AudioSource* _audioSource;
	char _hasData;
	char _hasProcessedData;
	void* _samples;
	void* _processedSamples;
} BasicSpectrogramData_t;
struct Spectrogram;
typedef struct __attribute__((__packed__)) Spectrogram {
	char _unused_data_useless[0xC];

	void* _meshRenderers;
	struct BasicSpectrogramData* _spectrogramData;
} Spectrogram_t;
struct StaticEnvironmentLights;
typedef struct __attribute__((__packed__)) StaticEnvironmentLights {
	char _unused_data_useless[0xC];

	struct Color _lightColors;
	void* _materials;
} StaticEnvironmentLights_t;
struct TrackLaneRingsManager;
struct TrackLaneRing;
typedef struct __attribute__((__packed__)) TrackLaneRing {
	char _unused_data_useless[0xC];

	float _rotZ;
	float _destRotZ;
	float _rotateSpeed;
	float _destPosZ;
	float _moveSpeed;
	struct Vector3 _positionOffset;
	void* _transform;
} TrackLaneRing_t;
typedef struct __attribute__((__packed__)) TrackLaneRingsManager {
	char _unused_data_useless[0xC];

	struct TrackLaneRing* _trackLaneRingPrefab;
	int _ringCount;
	float _ringPositionStep;
	struct TrackLaneRing* _rings;
} TrackLaneRingsManager_t;
struct TrackLaneRingsPositionStepEffectSpawner;
typedef struct __attribute__((__packed__)) TrackLaneRingsPositionStepEffectSpawner {
	char _unused_data_useless[0xC];

	struct TrackLaneRingsManager* _trackLaneRingsManager;
	enum BeatmapEventType _beatmapEventType;
	float _minPositionStep;
	float _maxPositionStep;
	float _moveSpeed;
	struct BeatmapObjectCallbackController* _beatmapObjectCallbackController;
	char _prevWasMinStep;
} TrackLaneRingsPositionStepEffectSpawner_t;
struct TrackLaneRingsRotationEffect;
typedef struct __attribute__((__packed__)) TrackLaneRingsRotationEffect {
	char _unused_data_useless[0xC];

	struct TrackLaneRingsManager* _trackLaneRingsManager;
	float _startupRotationAngle;
	float _startupRotationStep;
	float _startupRotationPropagationSpeed;
	float _startupRotationFlexySpeed;
	void* _activeRingRotationEffects;
	void* _ringRotationEffectsPool;
	void* effectIndicesToDelete;
} TrackLaneRingsRotationEffect_t;
struct TrackLaneRingsRotationEffectSpawner;
typedef struct __attribute__((__packed__)) TrackLaneRingsRotationEffectSpawner {
	char _unused_data_useless[0xC];

	struct TrackLaneRingsRotationEffect* _trackLaneRingsRotationEffect;
	enum BeatmapEventType _beatmapEventType;
	float _rotationStep;
	float _rotationPropagationSpeed;
	float _rotationFlexySpeed;
	struct BeatmapObjectCallbackController* _beatmapObjectCallbackController;
} TrackLaneRingsRotationEffectSpawner_t;
struct ComboUIController;
typedef struct __attribute__((__packed__)) ComboUIController {
	char _unused_data_useless[0xC];

	struct TextMeshProUGUI* _comboText;
	void* _animator;
	struct ScoreController* _scoreController;
	int _comboLostID;
	char _comboLost;
} ComboUIController_t;
struct FeverModeUIPanel;
typedef struct __attribute__((__packed__)) FeverModeUIPanel {
	char _unused_data_useless[0xC];

	void* _feverBGTextRectTransform;
	struct ScoreController* _scoreController;
	float _feverTextRectWidth;
} FeverModeUIPanel_t;
struct GameEnergyUIPanel;
typedef struct __attribute__((__packed__)) GameEnergyUIPanel {
	char _unused_data_useless[0xC];

	struct Image* _energyBar;
	struct Image* _batteryLifeSegmentPrefab;
	float _batterySegmentSeparatorWidth;
	float _batterySegmentHorizontalPadding;
	struct GameEnergyCounter* _gameEnergyCounter;
	void* _batteryLifeSegments;
	int _activeBatteryLifeSegmentsCount;
} GameEnergyUIPanel_t;
struct ImmediateRankUIPanel;
typedef struct __attribute__((__packed__)) ImmediateRankUIPanel {
	char _unused_data_useless[0xC];

	struct TextMeshProUGUI* _rankText;
	struct TextMeshProUGUI* _relativeScoreText;
	struct RelativeScoreAndImmediateRankCounter* _relativeScoreAndImmediateRankCounter;
	void* _stringBuilder;
	float _prevRelativeScore;
	enum Rank _prevImmediateRank;
} ImmediateRankUIPanel_t;
struct MissionObjectiveGameUIView;
typedef struct __attribute__((__packed__)) MissionObjectiveGameUIView {
	char _unused_data_useless[0xC];

	void* _notFailedIcon;
	void* _failedIcon;
	void* _notClearedIcon;
	void* _clearedIcon;
	struct Image* _resultIcon;
	struct Color _finalClearIconColor;
	struct Color _finalFailIconColor;
	struct Color _nonFinalIconColor;
	void* _clearedPS;
	int _numberOfParticles;
	struct TextMeshProUGUI* _nameText;
	struct TextMeshProUGUI* _valueText;
	struct TextMeshProUGUI* _conditionText;
	struct MissionObjectiveChecker* _missionObjectiveChecker;
} MissionObjectiveGameUIView_t;
struct MissionObjectivesGameUIController;
typedef struct __attribute__((__packed__)) MissionObjectivesGameUIController {
	char _unused_data_useless[0xC];

	struct MissionObjectiveCheckersManager* _missionObjectiveCheckersManager;
	struct MissionObjectiveGameUIView* _missionObjectiveGameUIViewPrefab;
	void* _backgroundGO;
	float _separator;
	float _elementWidth;
	void* _missionObjectiveGameUIViews;
} MissionObjectivesGameUIController_t;
struct NoteCutDeviationText;
typedef struct __attribute__((__packed__)) NoteCutDeviationText {
	char _unused_data_useless[0xC];

	struct TextMeshProUGUI* _text;
	struct BeatmapObjectSpawnController* _beatmapObjectSpawnController;
} NoteCutDeviationText_t;
struct ScoreMultiplierUIController;
typedef struct __attribute__((__packed__)) ScoreMultiplierUIController {
	char _unused_data_useless[0xC];

	struct TextMeshProUGUI* _multiplierTexts;
	struct Image* _multiplierProgressImage;
	void* _multiplierAnimator;
	struct ScoreController* _scoreController;
	int _prevMultiplier;
	int _multiplierIncreasedTriggerId;
	float _progressTarget;
} ScoreMultiplierUIController_t;
struct ScoreUIController;
enum ScoreDisplayType {
	ScoreDisplayType_RawScore,
	ScoreDisplayType_ModifiedScore
};
typedef struct __attribute__((__packed__)) ScoreUIController {
	char _unused_data_useless[0xC];

	struct TextMeshProUGUI* _scoreText;
	struct ScoreController* _scoreController;
	enum ScoreDisplayType scoreDisplayType;
	void* _stringBuilder;
} ScoreUIController_t;
struct SongProgressUIController;
struct Slider;
enum Direction {
	Direction_LeftToRight,
	Direction_RightToLeft,
	Direction_BottomToTop,
	Direction_TopToBottom
};
typedef struct __attribute__((__packed__)) Slider {
	char _unused_data_useless[0x94];

	void* m_FillRect;
	void* m_HandleRect;
	enum Direction m_Direction;
	float m_MinValue;
	float m_MaxValue;
	char m_WholeNumbers;
	float m_Value;
	void* m_OnValueChanged;
	struct Image* m_FillImage;
	void* m_FillTransform;
	void* m_FillContainerRect;
	void* m_HandleTransform;
	void* m_HandleContainerRect;
	struct Vector2 m_Offset;
	void* m_Tracker;
} Slider_t;
typedef struct __attribute__((__packed__)) SongProgressUIController {
	char _unused_data_useless[0xC];

	struct Slider* _slider;
	struct Image* _progressImage;
	struct TextMeshProUGUI* _durationMinutesText;
	struct TextMeshProUGUI* _durationSecondsText;
	struct TextMeshProUGUI* _progressMinutesText;
	struct TextMeshProUGUI* _progressSecondsText;
	struct AudioTimeSyncController* _audioTimeSyncController;
	int _prevMinutes;
	int _prevSeconds;
	void* _stringBuilder;
} SongProgressUIController_t;
struct SongTimeAnimationPlayer;
typedef struct __attribute__((__packed__)) SongTimeAnimationPlayer {
	char _unused_data_useless[0xC];

	void* _songTime;
	void* _animationClip;
} SongTimeAnimationPlayer_t;
struct EffectPoolsInstaller;
typedef struct __attribute__((__packed__)) EffectPoolsInstaller {
	char _unused_data_useless[0x10];

	struct FlyingTextEffect* _flyingTextEffectPrefab;
	struct FlyingScoreEffect* _flyingScoreEffectPrefab;
	struct BeatEffect* _beatEffectPrefab;
	struct NoteCutSoundEffect* _noteCutSoundEffectPrefab;
	struct BombCutSoundEffect* _bombCutSoundEffectPrefab;
	struct FlyingSpriteEffect* _flyingSpriteEffectPrefab;
	void* _noteDebrisHDConditionVariable;
	struct NoteDebris* _noteDebrisHDPrefab;
	struct NoteDebris* _noteDebrisLWPrefab;
} EffectPoolsInstaller_t;
struct GameCoreInstaller;
typedef struct __attribute__((__packed__)) GameCoreInstaller {
	char _unused_data_useless[0x10];

	void* _pauseButtonPressDurationLevel;
	struct BasicSaberModelController* _basicSaberModelControllerPrefab;
} GameCoreInstaller_t;
struct GameplayCoreBeatmapObjectPoolsInstaller;
typedef struct __attribute__((__packed__)) GameplayCoreBeatmapObjectPoolsInstaller {
	char _unused_data_useless[0x14];

	struct NoteController* _normalBasicNotePrefab;
	struct BombNoteController* _bombNotePrefab;
	struct ObstacleController* _obstacleTopPrefab;
	struct ObstacleController* _obstacleFullHeightPrefab;
	struct NoteLineConnectionController* _noteLineConnectionControllerPrefab;
	struct BeatLineController* _beatLinePrefab;
} GameplayCoreBeatmapObjectPoolsInstaller_t;
struct MainSettingsMenuViewControllersInstaller;
typedef struct __attribute__((__packed__)) MainSettingsMenuViewControllersInstaller {
	char _unused_data_useless[0x10];

	struct MainSettingsMenuViewController* _defaultSettingsMenuViewController;
	struct MainSettingsMenuViewController* _questSettingsMenuViewController;
	struct MainSettingsMenuViewController* _psvrSettingsMenuViewController;
} MainSettingsMenuViewControllersInstaller_t;
struct TutorialBeatmapObjectPoolsInstaller;
typedef struct __attribute__((__packed__)) TutorialBeatmapObjectPoolsInstaller {
	char _unused_data_useless[0x10];

	struct NoteController* _basicNotePrefab;
	struct BombNoteController* _bombNotePrefab;
	struct ObstacleController* _obstacleTopPrefab;
	struct ObstacleController* _obstacleFullHeightPrefab;
	struct NoteLineConnectionController* _noteLineConnectionControllerPrefab;
} TutorialBeatmapObjectPoolsInstaller_t;
struct AchievementsEvaluationHandler;
typedef struct __attribute__((__packed__)) AchievementsEvaluationHandler {
	char _unused_data_useless[0xC];

	struct AchievementsModelSO* _achievementsModel;
	void* _clearedLevel100Achievement;
	void* _totalScore100MillionAchievement;
	void* _24HoursPlayedAchievement;
	void* _kilometersTravelled100Achievement;
	void* _15ExpertLevelsRankSAchievement;
	void* _15ExpertLevelsFullComboAchievement;
	void* _15HardLevelsRankSAchievement;
	void* _15HardLevelsFullComboAchievement;
	void* _expertLevelClearedWithoutModifiersAchievement;
	void* _fullComboExpertWithoutModifiersAchievement;
	void* _goodCuts10000Achievement;
	void* _resultMinRankANormalWithoutModifiersAchievement;
	void* _resultMinRankSHardWithoutModifiersAchievement;
	void* _resultMinRankSSExpertWithoutModifiersAchievement;
	void* _combo50NormalWithoutModifiersAchievement;
	void* _combo100HardWithoutModifiersAchievement;
	void* _combo500ExpertWithoutModifiersAchievement;
	void* _clearedLevelWithoutModifiersAchievement;
	void* _clearedLevelWithSongSpeedFasterModifierAchievement;
	void* _clearedLevelWithInstaFailModifierAchievement;
	void* _clearedLevelWithDisappearingArrowsModifierAchievement;
	void* _clearedLevelWithBatteryEnergyModifierAchievement;
	void* _cleared30MissionsAchievement;
	void* _finalMissionClearedAchievement;
	void* _allMissionClearedAchievement;
	struct PlayerDataModelSO* _playerDataModel;
	struct SoloFreePlayFlowCoordinator* _soloFreePlayFlowCoordinator;
	struct CampaignFlowCoordinator* _campaignFlowCoordinator;
	struct PartyFreePlayFlowCoordinator* _partyFreePlayFlowCoordinator;
	struct MissionNodesManager* _missionNodesManager;
} AchievementsEvaluationHandler_t;
struct FinishTutorialAchievementHandler;
typedef struct __attribute__((__packed__)) FinishTutorialAchievementHandler {
	char _unused_data_useless[0xC];

	struct AchievementsModelSO* _achievementsModel;
	struct Signal* _tutorialFinishedSignal;
	void* _finishTutorialAchievement;
} FinishTutorialAchievementHandler_t;
struct AudioManagerSO;
typedef struct __attribute__((__packed__)) AudioManagerSO {
	char _unused_data_useless[0xC];

	void* _audioMixer;
	float _defaultSFXVolume;
	float _spatializerPluginLatancy;
	float _spatializerSFXVolumeOffset;
	float _sfxVolumeOffset;
} AudioManagerSO_t;
struct BeatmapObjectExecutionRatingsRecorder;
typedef struct __attribute__((__packed__)) BeatmapObjectExecutionRatingsRecorder {
	char _unused_data_useless[0xC];

	struct ScoreController* _scoreController;
	struct BeatmapObjectSpawnController* _beatmapObjectSpawnController;
	struct PlayerHeadAndObstacleInteraction* _playerHeadAndObstacleInteraction;
	struct AudioTimeSyncController* _audioTimeSyncController;
	void* _beatmapObjectExecutionRatings;
	void* _hitObstacles;
	void* _prevIntersectingObstacles;
	void* _afterCutScoreHandlers;
	void* _unusedAfterCutScoreHandlers;
} BeatmapObjectExecutionRatingsRecorder_t;
struct BeatmapObjectSpawnController;
typedef struct __attribute__((__packed__)) BeatmapObjectSpawnController {
	char _unused_data_useless[0xC];

	float _noteLinesDistance;
	float _globalYJumpOffset;
	float _maxHalfJumpDistance;
	float _halfJumpDurationInBeats;
	float _baseLinesHighestJumpPosY;
	float _upperLinesHighestJumpPosY;
	float _topLinesHighestJumpPosY;
	float _topLinesZPosOffset;
	float _moveSpeed;
	float _moveDurationInBeats;
	float _baseLinesYPos;
	float _upperLinesYPos;
	float _topLinesYPos;
	float _verticalObstaclePosY;
	float _topObstaclePosY;
	struct BeatmapObjectCallbackController* _beatmapObjectCallbackController;
	void* _noteAPool;
	void* _noteBPool;
	void* _bombNotePool;
	void* _fullHeightObstaclePool;
	void* _topObstaclePool;
	void* _noteLineConnectionPool;
	void* beatmapObjectWasSpawnedEvent;
	void* noteWasMissedEvent;
	void* noteWasCutEvent;
	void* noteDidStartJumpEvent;
	void* obstacleDiStartMovementEvent;
	void* obstacleDidFinishMovementEvent;
	void* obstacleDidPassThreeQuartersOfMove2Event;
	void* obstacleDidPassAvoidedMarkEvent;
	float _spawnAheadTime;
	float _jumpDistance;
	float _moveDistance;
	char _disableSpawning;
	int _beatmapObjectCallbackId;
	int _lateEventCallbackId;
	int _earlyEventCallbackId;
	float _beatsPerMinute;
	float _noteLinesCount;
	float _noteJumpMovementSpeed;
	char _disappearingArrows;
	char _ghostNotes;
	struct NoteController* _prevSpawnedNormalNoteController;
	int _numberOfSpawnedBasicNotes;
	float _firstBasicNoteTime;
} BeatmapObjectSpawnController_t;
struct ColorManager;
typedef struct __attribute__((__packed__)) ColorManager {
	char _unused_data_useless[0xC];

	struct PlayerDataModelSO* _playerModel;
	void* _colorA;
	void* _colorB;
	void* colorsDidChangeEvent;
} ColorManager_t;
struct GameEnergyCounter;
typedef struct __attribute__((__packed__)) GameEnergyCounter {
	char _unused_data_useless[0xC];

	float _badNoteEnergyDrain;
	float _missNoteEnergyDrain;
	float _hitBombEnergyDrain;
	float _goodNoteEnergyCharge;
	float _obstacleEnergyDrainPerSecond;
	int _batteryLives;
	struct SaberClashChecker* _saberClashChecker;
	struct BeatmapObjectSpawnController* _beatmapObjectSpawnController;
	struct PlayerHeadAndObstacleInteraction* _playerHeadAndObstacleInteraction;
	void* didInitializeEvent;
	void* gameEnergyDidReach0Event;
	void* gameEnergyDidChangeEvent;
	float energy_k__BackingField;
	enum EnergyType energyType_k__BackingField;
	char noFail_k__BackingField;
	char instaFail_k__BackingField;
	char failOnSaberClash_k__BackingField;
	char isInitialized_k__BackingField;
} GameEnergyCounter_t;
struct MissionLevelGameplayManager;
enum GameState {
	GameState_Intro,
	GameState_Playing,
	GameState_Paused,
	GameState_Finished,
	GameState_Failed
};
struct VRPlatformHelper;
enum VRPlatformSDK {
	VRPlatformSDK_OpenVR,
	VRPlatformSDK_Oculus,
	VRPlatformSDK_Unknown
};
struct OpenVRHelper;
struct TrackedDevicePose_t;
struct HmdMatrix34_t;
typedef struct __attribute__((__packed__)) HmdMatrix34_t {
	float m0;
	float m1;
	float m2;
	float m3;
	float m4;
	float m5;
	float m6;
	float m7;
	float m8;
	float m9;
	float m10;
	float m11;
} HmdMatrix34_t_t;
struct HmdVector3_t;
typedef struct __attribute__((__packed__)) HmdVector3_t {
	float v0;
	float v1;
	float v2;
} HmdVector3_t_t;
enum ETrackingResult {
	ETrackingResult_Uninitialized,
	ETrackingResult_Calibrating_InProgress,
	ETrackingResult_Calibrating_OutOfRange,
	ETrackingResult_Running_OK,
	ETrackingResult_Running_OutOfRange
};
typedef struct __attribute__((__packed__)) TrackedDevicePose_t {
	struct HmdMatrix34_t mDeviceToAbsoluteTracking;
	struct HmdVector3_t vVelocity;
	struct HmdVector3_t vAngularVelocity;
	enum ETrackingResult eTrackingResult;
	char bPoseIsValid;
	char bDeviceIsConnected;
} TrackedDevicePose_t_t;
typedef struct __attribute__((__packed__)) OpenVRHelper {
	char _unused_data_useless[0x8];

	void* inputFocusWasCapturedEvent;
	void* inputFocusWasReleasedEvent;
	void* dashboardWasActivatedEvent;
	void* dashboardWasDectivatedEvent;
	void* _disabledEventSystem;
	struct TrackedDevicePose_t _poses;
	struct TrackedDevicePose_t _gamePoses;
} OpenVRHelper_t;
struct OculusVRHelper;
struct OVRHapticsClip;
typedef struct __attribute__((__packed__)) OVRHapticsClip {
	char _unused_data_useless[0x8];

	int Count_k__BackingField;
	int Capacity_k__BackingField;
	void* Samples_k__BackingField;
} OVRHapticsClip_t;
typedef struct __attribute__((__packed__)) OculusVRHelper {
	char _unused_data_useless[0x8];

	void* inputFocusWasCapturedEvent;
	void* inputFocusWasReleasedEvent;
	void* hmdUnmountedEvent;
	void* hmdMountedEvent;
	struct OVRHapticsClip* _hapticsClip;
	char _userPresent;
	char _hasInputFocus;
	char _hasVrFocus;
} OculusVRHelper_t;
typedef struct __attribute__((__packed__)) VRPlatformHelper {
	char _unused_data_useless[0xC];

	void* inputFocusWasCapturedEvent;
	void* inputFocusWasReleasedEvent;
	void* dashboardWasActivatedEvent;
	void* dashboardWasDectivatedEvent;
	void* hmdUnmountedEvent;
	void* hmdMountedEvent;
	enum VRPlatformSDK vrPlatformSDK_k__BackingField;
	struct OpenVRHelper* _openVRHeper;
	struct OculusVRHelper* _oculusVRHelper;
} VRPlatformHelper_t;
typedef struct __attribute__((__packed__)) MissionLevelGameplayManager {
	char _unused_data_useless[0xC];

	struct Signal* _levelFailedSignal;
	struct Signal* _levelFinishedSignal;
	struct Signal* _pauseMenuDidFinishWithContinueSignal;
	struct MissionObjectiveCheckersManager* _missionObjectiveCheckersManager;
	void* _pauseTrigger;
	struct GameSongController* _gameSongController;
	struct GameEnergyCounter* _gameEnergyCounter;
	struct GamePauseManager* _gamePauseManager;
	enum GameState _gameState;
	struct VRPlatformHelper* _vrPlatformHelper;
} MissionLevelGameplayManager_t;
struct StandardLevelGameplayManager;
typedef struct __attribute__((__packed__)) StandardLevelGameplayManager {
	char _unused_data_useless[0xC];

	struct Signal* _levelFailedSignal;
	struct Signal* _levelFinishedSignal;
	struct Signal* _pauseMenuDidFinishWithContinueSignal;
	void* _pauseTrigger;
	struct GameSongController* _gameSongController;
	struct GameEnergyCounter* _gameEnergyCounter;
	struct GamePauseManager* _gamePauseManager;
	enum GameState _gameState;
	struct VRPlatformHelper* _vrPlatformHelper;
} StandardLevelGameplayManager_t;
struct GameSoundManager;
typedef struct __attribute__((__packed__)) GameSoundManager {
	char _unused_data_useless[0xC];

	struct AudioSource* _audioSource;
	struct AudioClip* _noteJumpAudioClips;
	struct AudioClip* _noteWasCutAudioClip;
	void* _noteJumpAudioClipPicker;
} GameSoundManager_t;
struct HapticFeedbackController;
typedef struct __attribute__((__packed__)) HapticFeedbackController {
	char _unused_data_useless[0xC];

	void* _controllersRumbleEnabled;
	void* _continuousRumbles;
	int continousRumbleIntervalCounter;
} HapticFeedbackController_t;
struct MissionLevelFailedController;
typedef struct __attribute__((__packed__)) MissionLevelFailedController {
	char _unused_data_useless[0xC];

	struct PrepareLevelCompletionResults* _prepareLevelCompletionResults;
	void* _levelFailedTextEffect;
	struct MissionLevelScenesTransitionSetupDataSO* _missionLevelSceneSetupData;
	struct MissionObjectiveCheckersManager* _missionObjectiveCheckersManager;
	struct BeatmapObjectSpawnController* _beatmapObjectSpawnController;
	struct GameSongController* _gameSongController;
	char autoRestart;
} MissionLevelFailedController_t;
struct MissionLevelFinishedController;
typedef struct __attribute__((__packed__)) MissionLevelFinishedController {
	char _unused_data_useless[0xC];

	struct PrepareLevelCompletionResults* _prepareLevelCompletionResults;
	struct MissionLevelScenesTransitionSetupDataSO* _missionLevelSceneSetupData;
	struct MissionObjectiveCheckersManager* _missionObjectiveCheckersManager;
} MissionLevelFinishedController_t;
struct MissionLevelReturnToMenuController;
typedef struct __attribute__((__packed__)) MissionLevelReturnToMenuController {
	char _unused_data_useless[0xC];

	struct MissionLevelScenesTransitionSetupDataSO* _missionLevelSceneSetupData;
	struct PrepareLevelCompletionResults* _prepareLevelCompletionResults;
} MissionLevelReturnToMenuController_t;
struct RestartTutorialController;
typedef struct __attribute__((__packed__)) RestartTutorialController {
	char _unused_data_useless[0xC];

	struct TutorialScenesTransitionSetupDataSO* _tutorialSceneSetupData;
} RestartTutorialController_t;
struct StandardLevelFailedController;
typedef struct __attribute__((__packed__)) StandardLevelFailedController {
	char _unused_data_useless[0xC];

	struct PrepareLevelCompletionResults* _prepareLevelCompletionResults;
	void* _levelFailedTextEffect;
	struct StandardLevelScenesTransitionSetupDataSO* _standardLevelSceneSetupData;
	struct BeatmapObjectSpawnController* _beatmapObjectSpawnController;
	struct GameSongController* _gameSongController;
	char autoRestart;
} StandardLevelFailedController_t;
struct StandardLevelFinishedController;
typedef struct __attribute__((__packed__)) StandardLevelFinishedController {
	char _unused_data_useless[0xC];

	struct PrepareLevelCompletionResults* _prepareLevelCompletionResults;
	struct StandardLevelScenesTransitionSetupDataSO* _standardLevelSceneSetupData;
} StandardLevelFinishedController_t;
struct StandardLevelRestartController;
typedef struct __attribute__((__packed__)) StandardLevelRestartController {
	char _unused_data_useless[0xC];

	struct StandardLevelScenesTransitionSetupDataSO* _standardLevelSceneSetupData;
	struct PrepareLevelCompletionResults* _prepareLevelCompletionResults;
} StandardLevelRestartController_t;
struct MainCamera;
typedef struct __attribute__((__packed__)) MainCamera {
	char _unused_data_useless[0xC];

	struct MainEffect* _mainEffect;
	void* _camera;
	void* _transform;
} MainCamera_t;
struct MissionObjectiveChecker;
enum Status {
	Status_None,
	Status_NotClearedYet,
	Status_NotFailedYet,
	Status_Cleared,
	Status_Failed
};
typedef struct __attribute__((__packed__)) MissionObjectiveChecker {
	char _unused_data_useless[0xC];

	struct MissionObjectiveTypeSO* _missionObjectiveType;
	void* statusDidChangeEvent;
	void* checkedValueDidChangeEvent;
	enum Status _status;
	int _checkedValue;
	struct MissionObjective* _missionObjective;
	char _disableChecking;
} MissionObjectiveChecker_t;
struct MissionObjectiveCheckersManager;
typedef struct __attribute__((__packed__)) MissionObjectiveCheckersManager {
	char _unused_data_useless[0xC];

	struct Signal* _levelFailedSignal;
	struct Signal* _levelFinishedSignal;
	struct MissionObjectiveChecker* _missionObjectiveCheckers;
	void* objectiveDidFailEvent;
	void* objectiveWasClearedEvent;
	void* objectivesListDidChangeEvent;
	struct MissionObjectiveChecker* _activeMissionObjectiveCheckers;
	char _isInitialized;
} MissionObjectiveCheckersManager_t;
struct MultiplierValuesRecorder;
typedef struct __attribute__((__packed__)) MultiplierValuesRecorder {
	char _unused_data_useless[0xC];

	struct ScoreController* _scoreController;
	struct AudioTimeSyncController* _audioTimeSyncController;
	void* _multiplierValues;
} MultiplierValuesRecorder_t;
struct PlayerController;
typedef struct __attribute__((__packed__)) PlayerController {
	char _unused_data_useless[0xC];

	struct Saber* _leftSaber;
	struct Saber* _rightSaber;
	struct SaberManager* _saberManager;
	void* _headTransform;
	char _overrideHeadPos;
	struct Vector3 _overriddenHeadPos;
	char _disableSabers;
	struct Vector3 _headPos;
} PlayerController_t;
struct PlayerHeadAndObstacleInteraction;
typedef struct __attribute__((__packed__)) PlayerHeadAndObstacleInteraction {
	char _unused_data_useless[0xC];

	struct ActiveObstaclesManager* _activeObstaclesManager;
	struct PlayerController* _playerController;
	int _lastFrameNumCheck;
	void* _intersectingObstacles;
} PlayerHeadAndObstacleInteraction_t;
struct PrepareLevelCompletionResults;
typedef struct __attribute__((__packed__)) PrepareLevelCompletionResults {
	char _unused_data_useless[0xC];

	struct GameplayModifiersModelSO* _gameplayModifiersModelSO;
	struct SaberActivityCounter* _saberActivityCounter;
	struct BeatmapObjectExecutionRatingsRecorder* _beatmapObjectExecutionRatingsRecorder;
	struct MultiplierValuesRecorder* _multiplierValuesRecorder;
	struct ScoreController* _scoreController;
	struct GameEnergyCounter* _gameEnergyCounter;
	struct GameSongController* _gameSongController;
	struct BeatmapDataModel* _beatmapDataModel;
	struct AudioTimeSyncController* _audioTimeSyncController;
	struct GameplayModifiers* _gameplayModifiers;
} PrepareLevelCompletionResults_t;
struct RelativeScoreAndImmediateRankCounter;
typedef struct __attribute__((__packed__)) RelativeScoreAndImmediateRankCounter {
	char _unused_data_useless[0xC];

	struct GameplayModifiersModelSO* _gameplayModifiersModel;
	struct ScoreController* _scoreController;
	void* relativeScoreOrImmediateRankDidChangeEvent;
	float relativeScore_k__BackingField;
	enum Rank immediateRank_k__BackingField;
	float _gameplayModifiersScoreMultiplier;
} RelativeScoreAndImmediateRankCounter_t;
struct SaberActivityCounter;
struct MovementHistoryRecorder;
struct AveragingValueRecorder;
typedef struct __attribute__((__packed__)) AveragingValueRecorder {
	char _unused_data_useless[0x8];

	float _averageWindowDuration;
	float _historyValuesPerSecond;
	int _historyValuesCount;
	void* _averageWindowValues;
	void* _historyValues;
	float _time;
	float _historyTime;
	float _averageValue;
	float _averageWindowValuesDuration;
	float _lastValue;
} AveragingValueRecorder_t;
typedef struct __attribute__((__packed__)) MovementHistoryRecorder {
	char _unused_data_useless[0x8];

	struct AveragingValueRecorder* _averagingValueRecorer;
	float _increaseSpeed;
	float _decreaseSpeed;
	float _accum;
} MovementHistoryRecorder_t;
typedef struct __attribute__((__packed__)) SaberActivityCounter {
	char _unused_data_useless[0xC];

	float _averageWindowDuration;
	float _valuesPerSecond;
	float _increaseSpeed;
	float _deceraseSpeed;
	float _movementSensitivityThreshold;
	struct PlayerController* _playerController;
	void* totalDistanceDidChangeEvent;
	struct Saber* _leftSaber;
	struct Saber* _rightSaber;
	struct Vector3 _prevLeftSaberTipPos;
	struct Vector3 _prevRightSaberTipPos;
	struct Vector3 _prevLeftHandPos;
	struct Vector3 _prevRightHandPos;
	char _hasPrevPos;
	float _leftSaberMovementDistance;
	float _rightSaberMovementDistance;
	float _leftHandMovementDistance;
	float _rightHandMovementDistance;
	struct MovementHistoryRecorder* _saberMovementHistoryRecorder;
	struct MovementHistoryRecorder* _handMovementHistoryRecorder;
} SaberActivityCounter_t;
struct GameplayCoreSceneSetup;
struct NoteBasicCutInfoSO;
typedef struct __attribute__((__packed__)) NoteBasicCutInfoSO {
	char _unused_data_useless[0xC];

	char strictAngles_k__BackingField;
} NoteBasicCutInfoSO_t;
typedef struct __attribute__((__packed__)) GameplayCoreSceneSetup {
	char _unused_data_useless[0x10];

	struct AudioTimeSyncController* _audioTimeSyncController;
	struct GameEnergyCounter* _gameEnergyCounter;
	struct ScoreController* _scoreController;
	struct RelativeScoreAndImmediateRankCounter* _relativeScoreAndImmediateRankCounter;
	struct BeatmapObjectCallbackController* _beatmapObjectCallbackController;
	struct BeatmapObjectSpawnController* _beatmapObjectSpawnController;
	struct BeatmapDataModel* _beatmapDataModel;
	struct AudioManagerSO* _audioMixer;
	struct NoteDebrisSpawner* _noteDebrisSpawner;
	void* _gameHUDGO;
	void* _songProgressPanelGO;
	void* _relativeScoreGO;
	void* _immediateRankGO;
	struct NoteCutEffectSpawner* _noteCutEffectSpawner;
	struct NoteCutSoundEffectManager* _noteCutSoundEffectManager;
	struct BeatmapCharacteristicSO* _oneColorBeatmapCharacteristic;
	struct NoteBasicCutInfoSO* _noteBasicCutInfo;
	struct PlayerController* _playerController;
	struct PrepareLevelCompletionResults* _prepareLevelCompletionResults;
	struct PauseMenuManager* _pauseMenuManager;
} GameplayCoreSceneSetup_t;
struct HealthWarningSceneSetup;
typedef struct __attribute__((__packed__)) HealthWarningSceneSetup {
	char _unused_data_useless[0x10];

	struct HealthWarningFlowCoordinator* _healthWarninglowCoordinator;
	struct VRUIHierarchyManager* _hierarchyManager;
} HealthWarningSceneSetup_t;
struct MenuSceneSetup;
struct FlowCoordinator;
struct VRUIViewController;
struct ButtonBinder;
typedef struct __attribute__((__packed__)) ButtonBinder {
	char _unused_data_useless[0x8];

	void* _bindings;
} ButtonBinder_t;
struct VRUIScreen;
typedef struct __attribute__((__packed__)) VRUIScreen {
	char _unused_data_useless[0xC];

	float _defaultYScale;
	struct VRUIViewController* _rootViewController;
	struct VRUIViewController* _placeholderViewController;
	float _destAnimationValue;
	char _initialized;
} VRUIScreen_t;
typedef struct __attribute__((__packed__)) VRUIViewController {
	char _unused_data_useless[0xC];

	void* didActivateEvent;
	void* didDeactivateEvent;
	struct ButtonBinder* _buttonBinder_k__BackingField;
	struct VRUINavigationController* _navigationController;
	struct VRUIViewController* _parentViewController;
	struct VRUIViewController* _childViewController;
	struct VRUIScreen* _screen;
	void* _rectTransform;
	void* _raycaster;
	char _wasActivatedBefore;
	char _isActivated;
	char _isInTransition;
} VRUIViewController_t;
typedef struct __attribute__((__packed__)) FlowCoordinator {
	char _unused_data_useless[0xC];

	void* _screenSystem;
	struct FlowCoordinator* _parentFlowCoordinator;
	struct FlowCoordinator* _childFlowCoordinator;
	void* _mainScreenViewControllers;
	struct VRUIViewController* _leftScreenViewController;
	struct VRUIViewController* _rightScreenViewController;
	struct VRUIViewController* _bottomScreenViewController;
	char _wasActivatedBefore;
	cs_string* _title;
	struct VRUIViewController* _providedMainViewController;
	struct VRUIViewController* _providedLeftViewController;
	struct VRUIViewController* _providedRightViewController;
	struct VRUIViewController* _providedBottomViewController;
	char _viewControllersWereProvided;
	char _isInDidActivatePhase;
	char _isActivated;
} FlowCoordinator_t;
typedef struct __attribute__((__packed__)) MenuSceneSetup {
	char _unused_data_useless[0x10];

	struct FlowCoordinator* _rootFlowCoordinator;
	struct VRUIHierarchyManager* _hierarchyManager;
} MenuSceneSetup_t;
struct MissionGameplaySceneSetup;
typedef struct __attribute__((__packed__)) MissionGameplaySceneSetup {
	char _unused_data_useless[0x10];

	struct MissionObjectiveCheckersManager* _missionObjectiveCheckersManager;
	struct MissionLevelFailedController* _missionLevelFailedController;
	struct ScoreUIController* _scoreUIController;
} MissionGameplaySceneSetup_t;
struct ScoreController;
typedef struct __attribute__((__packed__)) ScoreController {
	char _unused_data_useless[0xC];

	int _feverModeRequiredCombo;
	float _feverModeDuration;
	struct GameplayModifiersModelSO* _gameplayModifiersModel;
	struct BeatmapObjectSpawnController* _beatmapObjectSpawnController;
	struct PlayerHeadAndObstacleInteraction* _playerHeadAndObstacleInteraction;
	struct AudioTimeSyncController* _audioTimeSyncController;
	void* noteWasCutEvent;
	void* noteWasMissedEvent;
	void* scoreDidChangeEvent;
	void* immediateMaxPossibleScoreDidChangeEvent;
	void* multiplierDidChangeEvent;
	void* comboDidChangeEvent;
	void* feverModeChargeProgressDidChangeEvent;
	void* feverDidStartEvent;
	void* feverDidFinishEvent;
	void* comboBreakingEventHappenedEvent;
	int _baseRawScore;
	int _prevFrameRawScore;
	int _multiplier;
	int _multiplierIncreaseProgress;
	int _multiplierIncreaseMaxProgress;
	int _combo;
	int _maxCombo;
	char _feverIsActive;
	float _feverStartTime;
	int _feverCombo;
	char _playerHeadWasInObstacle;
	int _immediateMaxPossibleRawScore;
	int _cutOrMissedNotes;
	void* _afterCutScoreBuffers;
	float _gameplayModifiersScoreMultiplier;
} ScoreController_t;
struct GameSongController;
typedef struct __attribute__((__packed__)) GameSongController {
	char _unused_data_useless[0x10];

	struct AudioTimeSyncController* _audioTimeSyncController;
	struct AudioPitchGainEffect* _failAudioPitchGainEffect;
	struct BeatmapObjectCallbackController* _beatmapObjectCallbackController;
	char _songDidFinish;
} GameSongController_t;
struct AnchorIntoParent;
typedef struct __attribute__((__packed__)) AnchorIntoParent {
	char _unused_data_useless[0xC];

	void* _parentTransform;
	struct Vector3 _positionOffset;
} AnchorIntoParent_t;
struct AssetObjectListSO;
typedef struct __attribute__((__packed__)) AssetObjectListSO {
	char _unused_data_useless[0xC];

	void* _objects;
} AssetObjectListSO_t;
struct AverageSpeedComputer;
typedef struct __attribute__((__packed__)) AverageSpeedComputer {
	char _unused_data_useless[0xC];

	float _smoothUp;
	float _smoothDown;
	struct Vector3 _prevPos;
	float _speed;
} AverageSpeedComputer_t;
struct BuildSceneInfoListSO;
typedef struct __attribute__((__packed__)) BuildSceneInfoListSO {
	char _unused_data_useless[0xC];

	void* _sceneInfo;
} BuildSceneInfoListSO_t;
struct EnvironmentColorsSetter;
typedef struct __attribute__((__packed__)) EnvironmentColorsSetter {
	char _unused_data_useless[0xC];

	void* _colorsA;
	struct Color _overrideColorA;
	void* _colorsB;
	struct Color _overrideColorB;
	struct ColorManager* _colorManager;
	struct Color _originalColorsA;
	struct Color _originalColorsB;
} EnvironmentColorsSetter_t;
struct MultipliedAndAddedColorSO;
typedef struct __attribute__((__packed__)) MultipliedAndAddedColorSO {
	char _unused_data_useless[0xC];

	void* _baseColor;
	struct Color _multiplierColor;
	struct Color _addColor;
} MultipliedAndAddedColorSO_t;
struct MultipliedColorSO;
typedef struct __attribute__((__packed__)) MultipliedColorSO {
	char _unused_data_useless[0xC];

	void* _baseColor;
	struct Color _multiplierColor;
} MultipliedColorSO_t;
struct ConditionalImageMaterialSwitcher;
typedef struct __attribute__((__packed__)) ConditionalImageMaterialSwitcher {
	char _unused_data_useless[0xC];

	void* _material0;
	void* _material1;
	void* _value;
	struct Image* _image;
} ConditionalImageMaterialSwitcher_t;
struct ConditionalMaterialSwitcher;
typedef struct __attribute__((__packed__)) ConditionalMaterialSwitcher {
	char _unused_data_useless[0xC];

	void* _material0;
	void* _material1;
	void* _value;
	void* _renderer;
} ConditionalMaterialSwitcher_t;
struct ConditionalMove;
typedef struct __attribute__((__packed__)) ConditionalMove {
	char _unused_data_useless[0xC];

	struct Vector3 _offset;
	void* _value;
	char _activateOnFalse;
} ConditionalMove_t;
struct ConditionalSpriteSwitcher;
typedef struct __attribute__((__packed__)) ConditionalSpriteSwitcher {
	char _unused_data_useless[0xC];

	void* _sprite0;
	void* _material0;
	void* _sprite1;
	void* _material1;
	void* _value;
	void* _spriteRenderer;
} ConditionalSpriteSwitcher_t;
struct DisableComponentOnNonSteam;
typedef struct __attribute__((__packed__)) DisableComponentOnNonSteam {
	char _unused_data_useless[0xC];

	void* _component;
} DisableComponentOnNonSteam_t;
struct FirstPersonFlyingController;
typedef struct __attribute__((__packed__)) FirstPersonFlyingController {
	char _unused_data_useless[0xC];

	float _moveSensitivity;
	void* _camera;
	float _cameraFov;
	struct VRCenterAdjust* _centerAdjust;
	struct VRController* _controller0;
	struct VRController* _controller1;
	struct VRInputModule* _vrInputModule;
	void* _controllerModels;
	struct MouseLook* _mouseLook;
	void* _cameraTransform;
} FirstPersonFlyingController_t;
struct MouseLook;
typedef struct __attribute__((__packed__)) MouseLook {
	char _unused_data_useless[0x8];

	float _xSensitivity;
	float _ySensitivity;
	char _clampVerticalRotation;
	float _minimumX;
	float _maximumX;
	char _smooth;
	float _smoothTime;
	char _lockCursor;
	struct Quaternion _characterTargetRot;
	struct Quaternion _cameraTargetRot;
	char _cursorIsLocked;
} MouseLook_t;
struct CachedMediaAsyncLoaderSO;
typedef struct __attribute__((__packed__)) CachedMediaAsyncLoaderSO {
	char _unused_data_useless[0xC];

	int _maxNumberAdioClipCachedElements;
	int _maxNumberImageCachedElements;
	void* _audioCachedAsyncLoader;
	void* _texture2DCachedAsyncLoader;
} CachedMediaAsyncLoaderSO_t;
struct MoveBackWall;
typedef struct __attribute__((__packed__)) MoveBackWall {
	char _unused_data_useless[0xC];

	float _fadeInRegion;
	void* _meshRenderer;
	struct PlayerController* _playerController;
	float _thisZ;
	char _isVisible;
	void* _material;
} MoveBackWall_t;
struct SimpleVRNodeRecorder;
enum RecordMode {
	RecordMode_Record,
	RecordMode_Playback,
	RecordMode_Off
};
typedef struct __attribute__((__packed__)) SimpleVRNodeRecorder {
	char _unused_data_useless[0xC];

	void* _songTime;
	cs_string* _saveFilename;
	enum RecordMode _mode;
	enum XRNode _node;
	void* _playbackTransform;
	float _smooth;
	float _forwardOffset;
	void* _keyframes;
	int _keyframeIndex;
	struct Vector3 _prevPos;
	struct Quaternion _prevRot;
} SimpleVRNodeRecorder_t;
struct VRControllersRecorder;
enum Mode {
	Mode_Record,
	Mode_Playback,
	Mode_Off
};
typedef struct __attribute__((__packed__)) VRControllersRecorder {
	char _unused_data_useless[0xC];

	void* _recordingTextAsset;
	cs_string* _recordingFileName;
	enum Mode _mode;
	char _dontMoveHead;
	char _changeToNonVRCamera;
	struct Vector3 _headRotationOffset;
	struct Vector3 _headPositionOffset;
	float _headSmooth;
	float _cameraFOV;
	float _controllersTimeOffset;
	float _controllersSmooth;
	struct VRController* _controller0;
	struct VRController* _controller1;
	void* _headTransform;
	void* _camera;
	void* _recorderCamera;
	void* _spawnRotationTransform;
	struct AudioTimeSyncController* _audioTimeSyncController;
	void* _keyframes;
	int _keyframeIndex;
} VRControllersRecorder_t;
struct VRTrackersRecorder;
typedef struct __attribute__((__packed__)) VRTrackersRecorder {
	char _unused_data_useless[0xC];

	void* _songTime;
	cs_string* _saveFilename;
	enum RecordMode _mode;
	void* _originTransform;
	void* _playbackTransforms;
	void* _keyframes;
	int _keyframeIndex;
	void* _newPosesAction;
	struct Vector3 _loadedOriginPos;
	struct Quaternion _loadedOriginRot;
} VRTrackersRecorder_t;
struct KeyframeSerializable;
typedef struct __attribute__((__packed__)) KeyframeSerializable {
	char _unused_data_useless[0x8];

	struct TransformSerializable* _transforms;
	float _time;
} KeyframeSerializable_t;
struct TransformSerializable;
typedef struct __attribute__((__packed__)) TransformSerializable {
	char _unused_data_useless[0x8];

	float _xPos;
	float _yPos;
	float _zPos;
	float _xRot;
	float _yRot;
	float _zRot;
	float _wRot;
	char _valid;
} TransformSerializable_t;
struct BasicSaberModelController;
typedef struct __attribute__((__packed__)) BasicSaberModelController {
	char _unused_data_useless[0xC];

	struct SaberWeaponTrail* _saberWeaponTrail;
	struct SetSaberGlowColor* _setSaberGlowColors;
	struct SetSaberFakeGlowColor* _setSaberFakeGlowColors;
} BasicSaberModelController_t;
struct BlocksBlade;
typedef struct __attribute__((__packed__)) BlocksBlade {
	char _unused_data_useless[0xC];

	void* _elementMesh;
	void* _material;
	int _numberOfElements;
	float _radius;
	float _length;
	float _minVelocity;
	float _maxVelocity;
	float _elementWidth;
	float _minElementLength;
	float _maxElementLength;
	struct Color color_k__BackingField;
	void* _elements;
	struct Vector4 _positions;
	struct Vector4 _sizes;
	struct Vector4 _colors;
	struct Matrix4x4 _matrices;
	void* _materialPropertyBlock;
	int _layer;
} BlocksBlade_t;
struct BoxCuttableBySaber;
typedef struct __attribute__((__packed__)) BoxCuttableBySaber {
	char _unused_data_useless[0x10];

	void* _collider;
	char _canBeCut;
	float _radius;
} BoxCuttableBySaber_t;
struct Saber;
struct SaberHistoryData;
struct TimeAndPos;
typedef struct __attribute__((__packed__)) TimeAndPos {
	struct Vector3 topPos;
	struct Vector3 bottomPos;
	float time;
} TimeAndPos_t;
typedef struct __attribute__((__packed__)) SaberHistoryData {
	char _unused_data_useless[0x8];

	struct TimeAndPos _data;
	int _nextAddIndex;
	int _validCount;
} SaberHistoryData_t;
struct Cutter;
struct CuttableBySaberSortParams;
struct CuttableBySaber;
typedef struct __attribute__((__packed__)) CuttableBySaber {
	char _unused_data_useless[0xC];

	void* wasCutBySaberEvent;
} CuttableBySaber_t;
typedef struct __attribute__((__packed__)) CuttableBySaberSortParams {
	char _unused_data_useless[0x8];

	struct CuttableBySaber* cuttableBySaber;
	float distance;
	struct Vector3 pos;
} CuttableBySaberSortParams_t;
typedef struct __attribute__((__packed__)) Cutter {
	char _unused_data_useless[0x8];

	void* _colliders;
	struct CuttableBySaberSortParams* _cuttableBySaberSortParams;
	void* _comparer;
} Cutter_t;
typedef struct __attribute__((__packed__)) Saber {
	char _unused_data_useless[0xC];

	void* _topPos;
	void* _bottomPos;
	void* _handlePos;
	struct VRController* _vrController;
	struct SaberTypeObject* _saberType;
	char disableCutting_k__BackingField;
	struct SaberHistoryData* _historyData;
	void* _afterCutSwingRatingCounters;
	void* _unusedAfterCutSwingRatingCounters;
	struct Cutter* _cutter;
	char _prevValuesAreValid;
	float _bladeSpeed;
	float _time;
} Saber_t;
struct SaberManager;
typedef struct __attribute__((__packed__)) SaberManager {
	char _unused_data_useless[0xC];

	struct Saber* _leftSaber;
	struct Saber* _rightSaber;
	char _allowOnlyOneSaber;
	enum SaberType _oneSaberType;
} SaberManager_t;
struct SaberModelContainer;
typedef struct __attribute__((__packed__)) SaberModelContainer {
	char _unused_data_useless[0xC];

	struct SaberTypeObject* _saberTypeObject;
	void* _saberModelController;
} SaberModelContainer_t;
struct SaberSound;
typedef struct __attribute__((__packed__)) SaberSound {
	char _unused_data_useless[0xC];

	void* _saberTop;
	struct AudioSource* _audioSource;
	void* _pitchBySpeedCurve;
	void* _gainBySpeedCurve;
	float _speedMultiplier;
	float _upSmooth;
	float _downSmooth;
	float _noSoundTopThresholdSqr;
	struct Vector3 _prevPos;
	float _speed;
} SaberSound_t;
struct SaberTypeObject;
typedef struct __attribute__((__packed__)) SaberTypeObject {
	char _unused_data_useless[0xC];

	enum SaberType _saberType;
} SaberTypeObject_t;
struct SaberWeaponTrail;
typedef struct __attribute__((__packed__)) SaberWeaponTrail {
	char _unused_data_useless[0x54];

	struct ColorManager* _colorManager;
	struct Color _multiplierSaberColor;
	float _powColorValue;
	struct SaberTypeObject* _saberTypeObject;
} SaberWeaponTrail_t;
struct SetBlocksBladeSaberGlowColor;
typedef struct __attribute__((__packed__)) SetBlocksBladeSaberGlowColor {
	char _unused_data_useless[0xC];

	struct SaberTypeObject* _saber;
	struct ColorManager* _colorManager;
	struct BlocksBlade* _blocksBlade;
} SetBlocksBladeSaberGlowColor_t;
struct SetPSSaberGlowColor;
typedef struct __attribute__((__packed__)) SetPSSaberGlowColor {
	char _unused_data_useless[0xC];

	struct SaberTypeObject* _saber;
	struct ColorManager* _colorManager;
	void* _particleSystem;
} SetPSSaberGlowColor_t;
struct SetSaberBladeParams;
struct PropertyTintColorPair;
typedef struct __attribute__((__packed__)) PropertyTintColorPair {
	char _unused_data_useless[0x8];

	struct Color tintColor;
	cs_string* property;
} PropertyTintColorPair_t;
typedef struct __attribute__((__packed__)) SetSaberBladeParams {
	char _unused_data_useless[0xC];

	struct SaberTypeObject* _saber;
	struct ColorManager* _colorManager;
	void* _meshRenderer;
	struct PropertyTintColorPair* _propertyTintColorPairs;
} SetSaberBladeParams_t;
struct SetSaberFakeGlowColor;
typedef struct __attribute__((__packed__)) SetSaberFakeGlowColor {
	char _unused_data_useless[0xC];

	struct Color _tintColor;
	struct SaberTypeObject* _saberTypeObject;
	struct ColorManager* _colorManager;
	struct Parametric3SliceSpriteController* _parametric3SliceSprite;
} SetSaberFakeGlowColor_t;
struct SetSaberGlowColor;
typedef struct __attribute__((__packed__)) SetSaberGlowColor {
	char _unused_data_useless[0xC];

	struct SaberTypeObject* _saberTypeObject;
	struct ColorManager* _colorManager;
	void* _meshRenderer;
	struct PropertyTintColorPair* _propertyTintColorPairs;
	void* _materialPropertyBlock;
} SetSaberGlowColor_t;
struct SetTubeBloomPrePassLightColor;
typedef struct __attribute__((__packed__)) SetTubeBloomPrePassLightColor {
	char _unused_data_useless[0xC];

	void* _color;
	struct TubeBloomPrePassLight* _tubeLights;
} SetTubeBloomPrePassLightColor_t;
struct SetTubeBloomPrePassLightColorByID;
typedef struct __attribute__((__packed__)) SetTubeBloomPrePassLightColorByID {
	char _unused_data_useless[0xC];

	void* _color;
	int _lightsID;
} SetTubeBloomPrePassLightColorByID_t;
struct SphereCuttableBySaber;
typedef struct __attribute__((__packed__)) SphereCuttableBySaber {
	char _unused_data_useless[0x10];

	void* _collider;
	char _canBeCut;
} SphereCuttableBySaber_t;
struct SaberBurnMarkArea;
struct Plane;
typedef struct __attribute__((__packed__)) Plane {
	struct Vector3 m_Normal;
	float m_Distance;
} Plane_t;
typedef struct __attribute__((__packed__)) SaberBurnMarkArea {
	char _unused_data_useless[0xC];

	void* _saberBurnMarkLinePrefab;
	float _blackMarkLineRandomOffset;
	int _textureWidth;
	int _textureHeight;
	float _burnMarksFadeOutStrength;
	void* _fadeOutShader;
	struct PlayerController* _playerController;
	void* _renderer;
	int _fadeOutStrengthShaderPropertyID;
	struct Saber* _sabers;
	struct Plane _plane;
	struct Vector3 _prevBurnMarkPos;
	void* _prevBurnMarkPosValid;
	void* _lineRenderers;
	void* _camera;
	struct Vector3 _linePoints;
	void* _renderTextures;
	void* _emitParams;
	void* _fadeOutMaterial;
} SaberBurnMarkArea_t;
struct SaberBurnMarkSparkles;
typedef struct __attribute__((__packed__)) SaberBurnMarkSparkles {
	char _unused_data_useless[0xC];

	void* _sparklesPS;
	void* _burnMarksPSPrefab;
	void* _boxCollider;
	struct PlayerController* _playerController;
	struct Saber* _sabers;
	struct Plane _plane;
	struct Vector3 _prevBurnMarkPos;
	void* _prevBurnMarkPosValid;
	void* _burnMarksPS;
	void* _burnMarksEmmisionModules;
	void* _sparklesEmitParams;
} SaberBurnMarkSparkles_t;
struct SaberClashChecker;
typedef struct __attribute__((__packed__)) SaberClashChecker {
	char _unused_data_useless[0xC];

	float _minDistanceToClash;
	struct PlayerController* _playerController;
	char sabersAreClashing_k__BackingField;
	struct Vector3 clashingPoint_k__BackingField;
	struct Saber* _leftSaber;
	struct Saber* _rightSaber;
} SaberClashChecker_t;
struct EventTextBinding;
typedef struct __attribute__((__packed__)) EventTextBinding {
	char _unused_data_useless[0x8];

	struct Signal* _signal;
	cs_string* _text;
	struct TextFadeTransitions* _textFadeTransitions;
} EventTextBinding_t;
struct VRCenterAdjust;
typedef struct __attribute__((__packed__)) VRCenterAdjust {
	char _unused_data_useless[0xC];

	void* _roomCenter;
	void* _roomRotation;
} VRCenterAdjust_t;
struct GamePauseManager;
typedef struct __attribute__((__packed__)) GamePauseManager {
	char _unused_data_useless[0xC];

	struct Signal* _gameDidPauseSignal;
	struct Signal* _gameDidResumeSignal;
	struct GameEnergyCounter* _gameEnergyCounter;
	struct ScoreController* _scoreController;
	struct BeatmapObjectExecutionRatingsRecorder* _beatmapObjectExecutionRatingsRecorder;
	struct SongController* _songController;
	struct PlayerController* _playerController;
	char _pause;
} GamePauseManager_t;
struct PauseAnimationController;
typedef struct __attribute__((__packed__)) PauseAnimationController {
	char _unused_data_useless[0xC];

	void* _animator;
	struct BeatmapObjectSpawnController* _beatmapObjectSpawnController;
	void* resumeFromPauseAnimationDidFinishEvent;
} PauseAnimationController_t;
struct PauseMenuManager;
typedef struct __attribute__((__packed__)) PauseMenuManager {
	char _unused_data_useless[0xC];

	struct Signal* _didFinishWithContinueButtonSignal;
	struct Signal* _didFinishWithMenuButtonSignal;
	struct Signal* _didFinishWithRestartButtonSignal;
	struct PauseAnimationController* _pauseAnimationController;
	struct TextMeshProUGUI* _levelNameText;
	struct TextMeshProUGUI* _beatmapDifficultyText;
	struct Button* _continueButton;
	struct Button* _restartButton;
	struct Button* _backButton;
	void* _localizedBackButtonText;
	struct ButtonBinder* _buttonBinder;
	char _ignoreFirstFrameVRControllerInteraction;
} PauseMenuManager_t;
struct OculusLevelProductsModelSO;
typedef struct __attribute__((__packed__)) OculusLevelProductsModelSO {
	char _unused_data_useless[0xC];

	struct LevelPackProductData* _levelPackProductsData;
	void* _levelIdToProductData;
	void* _levelPackIdToProductData;
	void* _assetFileToSku;
} OculusLevelProductsModelSO_t;
struct LevelProductData;
typedef struct __attribute__((__packed__)) LevelProductData {
	char _unused_data_useless[0x8];

	cs_string* _levelId;
	cs_string* _sku;
	cs_string* _assetFile;
} LevelProductData_t;
struct LevelPackProductData;
typedef struct __attribute__((__packed__)) LevelPackProductData {
	char _unused_data_useless[0x8];

	cs_string* _sku;
	cs_string* _levelPackId;
	struct LevelProductData* _levelProductsData;
} LevelPackProductData_t;
struct PCInit;
struct MainSettingsModel;
typedef struct __attribute__((__packed__)) MainSettingsModel {
	char _unused_data_useless[0xC];

	void* vrResolutionScale;
	void* menuVRResolutionScaleMultiplier;
	void* useFixedFoveatedRenderingDuringGameplay;
	void* windowResolution;
	void* fullscreen;
	void* antiAliasingLevel;
	void* volume;
	void* controllersRumbleEnabled;
	void* roomCenter;
	void* roomRotation;
	void* mirrorGraphicsSettings;
	void* mainEffectGraphicsSettings;
	void* bloomPrePassGraphicsSettings;
	void* smokeGraphicsSettings;
	void* enableAlphaFeatures;
	void* pauseButtonPressDurationLevel;
	void* blurGrabPassEnabled;
	void* burnMarkTrailsEnabled;
	void* screenDisplacementEffectsEnabled;
	void* smoothCameraEnabled;
	void* smoothCameraFieldOfView;
	void* smoothCameraThirdPersonPosition;
	void* smoothCameraThirdPersonEulerAngles;
	void* smoothCameraThirdPersonEnabled;
	void* smoothCameraRotationSmooth;
	void* smoothCameraPositionSmooth;
	void* audioLatency;
	void* depthTextureEnabled;
	char playingForTheFirstTime_k__BackingField;
	char _playingForTheFirstTimeChecked;
	char _isLoaded;
} MainSettingsModel_t;
typedef struct __attribute__((__packed__)) PCInit {
	char _unused_data_useless[0xC];

	void* _initScenesTransitionSetupData;
	struct MainSettingsModel* _mainSettingsModel;
} PCInit_t;
struct SteamLevelProductsModelSO;
typedef struct __attribute__((__packed__)) SteamLevelProductsModelSO {
	char _unused_data_useless[0xC];

	struct LevelPackProductData* _levelPackProductsData;
	void* _levelIdToProductData;
	void* _levelPackIdToProductData;
} SteamLevelProductsModelSO_t;
struct PS4AchievementIdsModelSO;
typedef struct __attribute__((__packed__)) PS4AchievementIdsModelSO {
	char _unused_data_useless[0xC];

	void* _achievementsIds;
	void* _achievementIdToTrophyId;
	void* _trophyIdToAchievementId;
} PS4AchievementIdsModelSO_t;
struct AchievementIdData;
typedef struct __attribute__((__packed__)) AchievementIdData {
	char _unused_data_useless[0x8];

	int _trophyId;
	void* _achievement;
} AchievementIdData_t;
struct PS4Init;
struct PS4ActivePublisherSKUSettingsSO;
typedef struct __attribute__((__packed__)) PS4ActivePublisherSKUSettingsSO {
	char _unused_data_useless[0xC];

	struct PS4PublisherSKUSettingsSO* activePublisherSKUSettings;
} PS4ActivePublisherSKUSettingsSO_t;
typedef struct __attribute__((__packed__)) PS4Init {
	char _unused_data_useless[0xC];

	void* _psvrSetupScenesTransitionSetupData;
	struct MainSettingsModel* _mainSettingsModel;
	struct PS4ActivePublisherSKUSettingsSO* _activePublisherSKUSettingsSO;
} PS4Init_t;
struct PS4LeaderboardIdsModelSO;
typedef struct __attribute__((__packed__)) PS4LeaderboardIdsModelSO {
	char _unused_data_useless[0xC];

	void* _leaderboardIds;
	void* _leaderboardIdToPs4Id;
} PS4LeaderboardIdsModelSO_t;
struct LeaderboardIdData;
typedef struct __attribute__((__packed__)) LeaderboardIdData {
	char _unused_data_useless[0x8];

	unsigned int _ps4LeaderboardId;
	cs_string* _leaderboardId;
} LeaderboardIdData_t;
struct PS4OnGoingToBackgroundSaveHandler;
typedef struct __attribute__((__packed__)) PS4OnGoingToBackgroundSaveHandler {
	char _unused_data_useless[0xC];

	struct PlayerDataModelSO* _playerDataModel;
	struct LocalLeaderboardsModel* _localLeaderboardModel;
	struct MainSettingsModel* _mainSettingsModel;
} PS4OnGoingToBackgroundSaveHandler_t;
struct PS4PublisherSKUSettingsSO;
typedef struct __attribute__((__packed__)) PS4PublisherSKUSettingsSO {
	char _unused_data_useless[0xC];

	cs_string* _skuName;
	cs_string* _contentId;
	int _parentalLockLevel;
	cs_string* _npTitleFilenamePath;
	int _defaultAgeRestriction;
} PS4PublisherSKUSettingsSO_t;
struct PSVRInfoBar;
typedef struct __attribute__((__packed__)) PSVRInfoBar {
	char _unused_data_useless[0xC];

	struct VRUITitleBar* _vruiTitleBar;
} PSVRInfoBar_t;
struct PSVRInit;
typedef struct __attribute__((__packed__)) PSVRInit {
	char _unused_data_useless[0xC];

	void* _psvrSetupScenesTransitionSetupData;
	void* _initScenesTransitionSetupData;
} PSVRInit_t;
struct PSVRSaveAreaChecker;
typedef struct __attribute__((__packed__)) PSVRSaveAreaChecker {
	char _unused_data_useless[0xC];

	void* _infoTextRectTransform;
	void* _cameraTransform;
	void* _continueButton;
	void* _notInsideSafeAreaText;
} PSVRSaveAreaChecker_t;
struct QuestInit;
typedef struct __attribute__((__packed__)) QuestInit {
	char _unused_data_useless[0xC];

	void* _initScenesTransitionSetupData;
	struct MainSettingsModel* _mainSettingsModel;
} QuestInit_t;
struct PS4LevelProductsModelSO;
typedef struct __attribute__((__packed__)) PS4LevelProductsModelSO {
	char _unused_data_useless[0xC];

	struct LevelPackProductData* _levelPackProductsData;
	float _packLevelPriceDiscountMul;
	void* _levelIdToProductData;
	void* _levelPackIdToProductData;
} PS4LevelProductsModelSO_t;
struct CommandBufferGrabPass;
enum CameraEvent {
	CameraEvent_BeforeDepthTexture,
	CameraEvent_AfterDepthTexture,
	CameraEvent_BeforeDepthNormalsTexture,
	CameraEvent_AfterDepthNormalsTexture,
	CameraEvent_BeforeGBuffer,
	CameraEvent_AfterGBuffer,
	CameraEvent_BeforeLighting,
	CameraEvent_AfterLighting,
	CameraEvent_BeforeFinalPass,
	CameraEvent_AfterFinalPass,
	CameraEvent_BeforeForwardOpaque,
	CameraEvent_AfterForwardOpaque,
	CameraEvent_BeforeImageEffectsOpaque,
	CameraEvent_AfterImageEffectsOpaque,
	CameraEvent_BeforeSkybox,
	CameraEvent_AfterSkybox,
	CameraEvent_BeforeForwardAlpha,
	CameraEvent_AfterForwardAlpha,
	CameraEvent_BeforeImageEffects,
	CameraEvent_AfterImageEffects,
	CameraEvent_AfterEverything,
	CameraEvent_BeforeReflections,
	CameraEvent_AfterReflections,
	CameraEvent_BeforeHaloAndLensFlares,
	CameraEvent_AfterHaloAndLensFlares
};
typedef struct __attribute__((__packed__)) CommandBufferGrabPass {
	char _unused_data_useless[0x14];

	cs_string* _textureName;
	enum CameraEvent _cameraEvent;
} CommandBufferGrabPass_t;
struct MainEffect;
struct MainEffectRenderer;
typedef struct __attribute__((__packed__)) MainEffectRenderer {
	char _unused_data_useless[0xC];

	struct KawaseBlurRenderer* _kawaseBlurRenderer;
	struct MainEffectParams* _mainEffectParams;
	void* _mainEffectMaterial;
	void* _fadeMaterial;
	void* _fadeValue;
} MainEffectRenderer_t;
typedef struct __attribute__((__packed__)) MainEffect {
	char _unused_data_useless[0xC];

	struct MainEffectParams* _mainEffectParams;
	void* _fadeValue;
	struct KawaseBlurRenderer* _kawaseBlurRenderer;
	void* _mainEffectShader;
	void* _fadeShader;
	struct MainEffectRenderer* _mainEffectRenderer;
	void* _mainEffectMaterial;
	void* _fadeMaterial;
} MainEffect_t;
struct MainEffectParams;
typedef struct __attribute__((__packed__)) MainEffectParams {
	char _unused_data_useless[0xC];

	void* _postProcessEnabled;
	float _alphaWeights;
	float _baseColorBoost;
	float _baseColorBoostThreshold;
	int _bloomIterations;
	float _bloomIntensity;
	int _textureWidth;
} MainEffectParams_t;
struct MaterialPropertyBlockController;
typedef struct __attribute__((__packed__)) MaterialPropertyBlockController {
	char _unused_data_useless[0xC];

	void* _renderers;
	void* _materialPropertyBlock;
} MaterialPropertyBlockController_t;
struct Mirror;
typedef struct __attribute__((__packed__)) Mirror {
	char _unused_data_useless[0xC];

	struct MirrorRenderer* _mirrorRenderer;
	void* _renderer;
} Mirror_t;
struct MirrorRenderer;
struct LayerMask;
typedef struct __attribute__((__packed__)) LayerMask {
	int m_Mask;
} LayerMask_t;
struct Rect;
typedef struct __attribute__((__packed__)) Rect {
	float m_XMin;
	float m_YMin;
	float m_Width;
	float m_Height;
} Rect_t;
typedef struct __attribute__((__packed__)) MirrorRenderer {
	char _unused_data_useless[0xC];

	struct LayerMask _reflectLayers;
	int _stereoTextureWidth;
	int _stereoTextureHeight;
	int _monoTextureWidth;
	int _monoTextureHeight;
	int _maxAntiAliasing;
	char _disableDepthTexture;
	char _enableBloomPrePass;
	struct BloomPrePassRenderer* _bloomPrePassRenderer;
	struct BloomPrePassParams* _bloomPrePassParams;
	void* _activeRenderTexture;
	void* _stereoMirrorTexture;
	void* _monoMirrorTexture;
	void* _bloomPrePassRenderTexture;
	void* _mirrorCamera;
	struct Vector3 _prevCameraPos;
	struct Quaternion _prevCameraRotation;
	float _prevCameraFOV;
	int _prevFrameNum;
	int _antialiasing;
	void* _emptyTexture;
	struct Rect kLeftRect;
	struct Rect kRightRect;
	struct Rect kFullRect;
} MirrorRenderer_t;
struct ShaderVariant;
typedef struct __attribute__((__packed__)) ShaderVariant {
	char _unused_data_useless[0x8];

	struct Variant* _variants;
	void* _shader;
} ShaderVariant_t;
struct Variant;
enum PassType {
	PassType_Normal,
	PassType_Vertex,
	PassType_VertexLM,
	PassType_VertexLMRGBM,
	PassType_ForwardBase,
	PassType_ForwardAdd,
	PassType_LightPrePassBase,
	PassType_LightPrePassFinal,
	PassType_ShadowCaster,
	PassType_Deferred,
	PassType_Meta,
	PassType_MotionVectors,
	PassType_ScriptableRenderPipeline,
	PassType_ScriptableRenderPipelineDefaultUnlit
};
typedef struct __attribute__((__packed__)) Variant {
	char _unused_data_useless[0x8];

	enum PassType _passType;
	cs_string* _keywords;
} Variant_t;
struct VRRenderingParamsSetup;
enum SceneType {
	SceneType_Undefined,
	SceneType_Menu,
	SceneType_Game
};
typedef struct __attribute__((__packed__)) VRRenderingParamsSetup {
	char _unused_data_useless[0xC];

	void* _vrResolutionScale;
	void* _menuVRResolutionScaleMultiplier;
	void* _useFixedFoveatedRenderingDuringGameplay;
	enum SceneType _sceneType;
} VRRenderingParamsSetup_t;
struct SmoothCamera;
typedef struct __attribute__((__packed__)) SmoothCamera {
	char _unused_data_useless[0xC];

	void* _camera;
	struct MainCamera* _mainCamera;
	struct Vector3 _thirdPersonPosition;
	struct Vector3 _thirdPersonEulerAngles;
	char _thirdPersonEnabled;
	float _rotationSmooth;
	float _positionSmooth;
} SmoothCamera_t;
struct SmoothCameraController;
struct LIV;
typedef struct __attribute__((__packed__)) LIV {
	char _unused_data_useless[0xC];

	void* TrackedSpaceOrigin;
	void* HMDCamera;
	char DisableStandardAssets;
	struct LayerMask SpectatorLayerMask;
} LIV_t;
typedef struct __attribute__((__packed__)) SmoothCameraController {
	char _unused_data_useless[0xC];

	struct MainSettingsModel* _mainSettingsModel;
	struct SmoothCamera* _smoothCamera;
	struct LIV* _liv;
} SmoothCameraController_t;
struct BeatLineController;
typedef struct __attribute__((__packed__)) BeatLineController {
	char _unused_data_useless[0xC];

	struct TubeBloomPrePassLight* _tubeBloomPrePassLight;
	void* _arriveFadeCurve;
	void* _jumpFadeCurve;
	float _alphaMul;
	float _maxAlpha;
} BeatLineController_t;
struct BaseNoteVisuals;
typedef struct __attribute__((__packed__)) BaseNoteVisuals {
	char _unused_data_useless[0xC];

	struct NoteController* _noteController;
	struct CutoutAnimateEffect* _cutoutAnimateEffect;
} BaseNoteVisuals_t;
struct BombNoteController;
typedef struct __attribute__((__packed__)) BombNoteController {
	char _unused_data_useless[0x3C];

	struct CuttableBySaber* _cuttableBySaber;
	void* _wrapperGO;
} BombNoteController_t;
struct ColorNoteVisuals;
typedef struct __attribute__((__packed__)) ColorNoteVisuals {
	char _unused_data_useless[0xC];

	float _arrowGlowIntensity;
	struct ColorManager* _colorManager;
	struct NoteController* _noteController;
	void* _arrowGlowSpriteRenderer;
	void* _circleGlowSpriteRenderer;
	struct MaterialPropertyBlockController* _materialPropertyBlockControllers;
	void* _arrowMeshRenderer;
	void* didInitEvent;
	struct Color _noteColor;
} ColorNoteVisuals_t;
struct DisappearingArrowController;
typedef struct __attribute__((__packed__)) DisappearingArrowController {
	char _unused_data_useless[0xC];

	struct ColorNoteVisuals* _colorNoteVisuals;
	void* _spriteRenderers;
	void* _cubeMeshRenderer;
	struct MaterialPropertyBlockController* _materialPropertyBlockController;
	struct NoteMovement* _noteMovement;
	float _disappearingNormalStart;
	float _disappearingNormalEnd;
	float _disappearingGhostStart;
	float _disappearingGhostEnd;
	void* _initialSpriteAlphas;
	struct Vector3 _randomNoiseTexOffset;
	char _initialized;
	char _ghostNote;
	float _prevArrowTransparency;
	float _minDistance;
	float _maxDistance;
} DisappearingArrowController_t;
struct GameNoteCollidersSizeController;
typedef struct __attribute__((__packed__)) GameNoteCollidersSizeController {
	char _unused_data_useless[0xC];

	struct GameNoteController* _gameNoteController;
	struct BoxCuttableBySaber* _bigCuttableBySaber;
	struct NoteMovement* _noteMovement;
	struct Vector3 _prevPos;
	char _prevPosIsValid;
	struct Vector3 _initColliderSize;
} GameNoteCollidersSizeController_t;
struct GameNoteController;
typedef struct __attribute__((__packed__)) GameNoteController {
	char _unused_data_useless[0x3C];

	struct BoxCuttableBySaber* _bigCuttableBySaber;
	struct BoxCuttableBySaber* _smallCuttableBySaber;
	struct NoteBasicCutInfoSO* _noteBasicCutInfo;
	struct DisappearingArrowController* _disappearingArrowController;
	void* _wrapperGO;
	struct AudioTimeSyncController* _audioTimeSyncController;
	char _disappearingArrow;
	char _ghostNote;
} GameNoteController_t;
struct GhostNoteController;
typedef struct __attribute__((__packed__)) GhostNoteController {
	char _unused_data_useless[0x3C];

	void* _wrapperGO;
} GhostNoteController_t;
struct NoteController;
typedef struct __attribute__((__packed__)) NoteController {
	char _unused_data_useless[0xC];

	struct NoteMovement* _noteMovement;
	void* _noteTransform;
	void* didInitEvent;
	void* noteDidStartJumpEvent;
	void* noteDidFinishJumpEvent;
	void* noteDidPassJumpThreeQuartersEvent;
	void* noteWasCutEvent;
	void* noteWasMissedEvent;
	void* noteDidStartDissolvingEvent;
	void* noteDidDissolveEvent;
	struct NoteData* _noteData;
	char _dissolving;
} NoteController_t;
struct NoteDebris;
typedef struct __attribute__((__packed__)) NoteDebris {
	char _unused_data_useless[0xC];

	struct ColorManager* _colorManager;
	void* _meshTransform;
	void* _rigidbody;
	struct MaterialPropertyBlockController* _materialPropertyBlockController;
	void* _cutoutCurve;
	void* _centroidComputationMesh;
	void* didFinishEvent;
	float _elapsedTime;
	float _lifeTime;
} NoteDebris_t;
struct NoteFloorMovement;
typedef struct __attribute__((__packed__)) NoteFloorMovement {
	char _unused_data_useless[0xC];

	void* _rotatedObject;
	struct PlayerController* _playerController;
	struct AudioTimeSyncController* _audioTimeSyncController;
	void* floorMovementDidFinishEvent;
	struct Vector3 _startPos;
	struct Vector3 _endPos;
	float _movementDuration;
	float _startTime;
	struct Vector3 _localPosition;
} NoteFloorMovement_t;
struct NoteJump;
typedef struct __attribute__((__packed__)) NoteJump {
	char _unused_data_useless[0xC];

	void* _rotatedObject;
	float _yAvoidanceUp;
	float _yAvoidanceDown;
	float _endDistanceOffest;
	struct PlayerController* _playerController;
	struct AudioTimeSyncController* _audioTimeSyncController;
	void* noteJumpDidFinishEvent;
	void* noteJumpDidPassMissedMarkerEvent;
	void* noteJumpDidPassThreeQuartersEvent;
	void* noteJumpDidPassHalfEvent;
	struct Vector3 _startPos;
	struct Vector3 _endPos;
	float _jumpDuration;
	float _startTime;
	float _startVerticalVelocity;
	struct Quaternion _startRotation;
	struct Quaternion _middleRotation;
	struct Quaternion _endRotation;
	float _gravity;
	float _yAvoidance;
	float _missedTime;
	char _missedMarkReported;
	char _threeQuartersMarkReported;
	char _halfJumpMarkReported;
	struct Vector3 _localPosition;
	struct Vector3 _randomRotations;
	int _randomRotationIdx;
} NoteJump_t;
struct NoteLineConnectionController;
typedef struct __attribute__((__packed__)) NoteLineConnectionController {
	char _unused_data_useless[0xC];

	struct ColorManager* _colorManager;
	void* _lineRenderer;
	struct PlayerController* _playerController;
	struct AudioTimeSyncController* _audioTimeSyncController;
	void* didFinishEvent;
	struct NoteController* _noteController0;
	struct NoteController* _noteController1;
	struct Color _color0;
	struct Color _color1;
	float _fadeOutStartDistance;
	float _fadeOutEndDistance;
	float _noteTime;
	char _didFinish;
} NoteLineConnectionController_t;
struct NoteMovement;
enum MovementPhase {
	MovementPhase_None,
	MovementPhase_MovingOnTheFloor,
	MovementPhase_Jumping
};
typedef struct __attribute__((__packed__)) NoteMovement {
	char _unused_data_useless[0xC];

	struct NoteFloorMovement* _floorMovement;
	struct NoteJump* _jump;
	float _zOffset;
	void* didInitEvent;
	void* noteDidStartJumpEvent;
	void* noteDidFinishJumpEvent;
	void* noteDidPassMissedMarkerEvent;
	void* noteDidPassHalfJumpEvent;
	void* noteDidPassJumpThreeQuartersEvent;
	enum MovementPhase movementPhase_k__BackingField;
	struct Vector3 _position;
	struct Vector3 _prevPosition;
} NoteMovement_t;
struct NoteVisualDebuger;
typedef struct __attribute__((__packed__)) NoteVisualDebuger {
	char _unused_data_useless[0xC];

	struct NoteController* _noteController;
	void* _text;
} NoteVisualDebuger_t;
struct TutorialNoteController;
typedef struct __attribute__((__packed__)) TutorialNoteController {
	char _unused_data_useless[0x3C];

	struct BoxCuttableBySaber* _cuttableBySaberCore;
	struct BoxCuttableBySaber* _cuttableBySaberBeforeNote;
	struct NoteBasicCutInfoSO* _noteBasicCutInfo;
	void* _wrapperGO;
	char _beforeNoteCutWasOK;
} TutorialNoteController_t;
struct ObstacleController;
typedef struct __attribute__((__packed__)) ObstacleController {
	char _unused_data_useless[0xC];

	struct ActiveObstaclesManager* _activeObstaclesManager;
	struct StretchableObstacle* _stretchableObstacle;
	float _height;
	float _endDistanceOffest;
	void* _visualWrappers;
	struct PlayerController* _playerController;
	struct AudioTimeSyncController* _audioTimeSyncController;
	void* didInitEvent;
	void* finishedMovementEvent;
	void* passedThreeQuartersOfMove2Event;
	void* passedAvoidedMarkEvent;
	void* didStartDissolvingEvent;
	void* didDissolveEvent;
	struct Vector3 _startPos;
	struct Vector3 _midPos;
	struct Vector3 _endPos;
	float _move1Duration;
	float _move2Duration;
	float _startTimeOffset;
	float _obstacleDuration;
	char _passedThreeQuartersOfMove2Reported;
	char _passedAvoidedMarkReported;
	float _passedAvoidedMarkTime;
	float _finishMovementTime;
	char _initialized;
	struct Bounds _bounds;
	char _dissolving;
	struct ObstacleData* _obstacleData;
} ObstacleController_t;
struct ObstacleDissolve;
typedef struct __attribute__((__packed__)) ObstacleDissolve {
	char _unused_data_useless[0xC];

	struct ObstacleController* _obstacleController;
	struct CutoutAnimateEffect* _cutoutAnimateEffect;
} ObstacleDissolve_t;
struct StretchableObstacle;
struct StretchableCube;
typedef struct __attribute__((__packed__)) StretchableCube {
	char _unused_data_useless[0xC];

	struct Vector2 _uvs;
	void* _mesh;
} StretchableCube_t;
typedef struct __attribute__((__packed__)) StretchableObstacle {
	char _unused_data_useless[0xC];

	float _edgeSize;
	float _coreOffset;
	void* _obstacleCore;
	struct StretchableCube* _stretchableCore;
	struct ParametricBoxFrameController* _obstacleFrame;
	struct ParametricBoxFakeGlowController* _obstacleFakeGlow;
	struct Bounds _bounds;
} StretchableObstacle_t;
struct IntroTutorialController;
typedef struct __attribute__((__packed__)) IntroTutorialController {
	char _unused_data_useless[0xC];

	struct BloomFog* _bloomFog;
	struct IntroTutorialRing* _redRing;
	struct IntroTutorialRing* _blueRing;
	void* _redRingWrapper;
	void* _blueRingWrapper;
	void* _textCanvasGroup;
	void* _shockWavePS;
	struct Signal* _gameDidPauseSignal;
	struct Signal* _gameDidResumeSignal;
	void* introTutorialWillFinishEvent;
	void* introTutorialDidFinishEvent;
	char _showingFinishAnimation;
	char _redRingWrapperActive;
	char _blueRingWrapperActive;
} IntroTutorialController_t;
struct IntroTutorialRing;
typedef struct __attribute__((__packed__)) IntroTutorialRing {
	char _unused_data_useless[0xC];

	struct Image* _progressImages;
	enum SaberType _saberType;
	void* _particleSystem;
	void* _canvasGroup;
	float _activationDuration;
	struct ColorManager* _colorManager;
	struct Image* _ringGLowImages;
	char _highlighted;
	float _emitNextParticleTimer;
	float _activationProgress;
	void* _sabersInside;
	char _sabersInsideAfterOnEnable;
} IntroTutorialRing_t;
struct TextFadeTransitions;
enum State {
	State_NotInTransition,
	State_FadingOut,
	State_FadingIn
};
typedef struct __attribute__((__packed__)) TextFadeTransitions {
	char _unused_data_useless[0xC];

	struct TextMeshProUGUI* _textLabel;
	void* _canvasGroup;
	float _fadeDuration;
	enum State _state;
	cs_string* _nextText;
	float _fade;
} TextFadeTransitions_t;
struct TutorialController;
typedef struct __attribute__((__packed__)) TutorialController {
	char _unused_data_useless[0xC];

	struct TutorialSongController* _tutorialSongController;
	struct IntroTutorialController* _introTutorialController;
	struct AudioFading* _audioFading;
	struct TutorialPauseManager* _pauseManager;
	struct TutorialScenesTransitionSetupDataSO* _tutorialSceneSetupData;
	struct Signal* _pauseMenuDidFinishWithContinueSignal;
	struct Signal* _tutorialIntroStartedSignal;
	struct Signal* _tutorialFinishedSignal;
	void* _pauseTrigger;
	char _doingOutroTransition;
	struct VRPlatformHelper* _vrPlatformHelper;
} TutorialController_t;
struct TutorialNoteCutEffectSpawner;
typedef struct __attribute__((__packed__)) TutorialNoteCutEffectSpawner {
	char _unused_data_useless[0xC];

	struct ColorManager* _colorManager;
	struct NoteCutParticlesEffect* _noteCutParticlesEffect;
	struct ShockwaveEffect* _shockwaveEffect;
	struct NoteDebrisSpawner* _noteDebrisSpawner;
	struct NoteCutHapticEffect* _noteCutHapticEffect;
	struct FlyingTextSpawner* _failFlyingTextSpawner;
	struct BombExplosionEffect* _bombExplosionEffect;
	struct BeatmapObjectSpawnController* _beatmapObjectSpawnController;
	char handleWrongSaberTypeAsGoodAndDontWarnOnBadCuts_k__BackingField;
} TutorialNoteCutEffectSpawner_t;
struct TutorialPauseManager;
typedef struct __attribute__((__packed__)) TutorialPauseManager {
	char _unused_data_useless[0xC];

	struct SongController* _songController;
	struct Signal* _gameDidPauseSignal;
	struct Signal* _gameDidResumeSignal;
	struct PlayerController* _playerController;
	char _pause;
} TutorialPauseManager_t;
struct TutorialSongController;
struct TutorialObjectSpawnData;
typedef struct __attribute__((__packed__)) TutorialObjectSpawnData {
	char _unused_data_useless[0x8];

	struct Signal* gameEvent;
	int beatOffset;
	int firstTimeBeatOffset;
} TutorialObjectSpawnData_t;
typedef struct __attribute__((__packed__)) TutorialSongController {
	char _unused_data_useless[0x10];

	struct BeatmapObjectSpawnController* _beatmapObjectSpawnController;
	struct BeatmapDataModel* _beatmapDataModel;
	struct AudioClip* _audioClip;
	struct AudioTimeSyncController* _audioTimeSyncController;
	float _songBPM;
	int _startWaitTimeInBeats;
	int _numberOfBeatsToSnap;
	int _obstacleDurationInBeats;
	struct Signal* _noteCuttingTutorialPartDidStartSignal;
	struct Signal* _noteCuttingInAnyDirectionDidStartSignal;
	struct Signal* _bombCuttingTutorialPartDidStartSignal;
	struct Signal* _leftObstacleTutorialPartDidStartSignal;
	struct Signal* _rightObstacleTutorialPartDidStartSignal;
	struct Signal* _topObstacleTutorialPartDidStartSignal;
	struct Signal* _noteWasCutOKSignal;
	struct Signal* _noteWasCutTooSoonSignal;
	struct Signal* _noteWasCutWithWrongColorSignal;
	struct Signal* _noteWasCutFromDifferentDirectionSignal;
	struct Signal* _noteWasCutWithSlowSpeedSignal;
	struct Signal* _bombWasCutSignal;
	char specialTutorialMode_k__BackingField;
	int _tutorialBeatmapObjectIndex;
	int _prevSpawnedBeatmapObjectIndex;
	int _nextBeatmapObjectId;
	struct TutorialObjectSpawnData* _normalModeTutorialObjectsSpawnData;
	struct TutorialObjectSpawnData* _specialModeTutorialObjectsSpawnData;
} TutorialSongController_t;
struct BasicUIAudioManager;
typedef struct __attribute__((__packed__)) BasicUIAudioManager {
	char _unused_data_useless[0xC];

	struct Signal* _buttonClickEvents;
	struct AudioSource* _audioSource;
	struct AudioClip* _clickSounds;
	float _minPitch;
	float _maxPitch;
	void* _randomSoundPicker;
} BasicUIAudioManager_t;
struct VisualMetronome;
typedef struct __attribute__((__packed__)) VisualMetronome {
	char _unused_data_useless[0xC];

	struct AudioSource* _audioSource;
	float _leftPadding;
	float _rightPadding;
	void* _ticker;
	void* _movingTicker;
	float _metronomeInterval;
	struct Vector2 _normalTickerSize;
	struct Vector2 _tickTickerSize0;
	struct Vector2 _tickTickerSize1;
	float _smooth;
	float _prevAudioTime;
	float _zeroOffset;
	float _direction;
	char _dontTickThisFrame;
} VisualMetronome_t;
struct BasicLevelParamsPanel;
typedef struct __attribute__((__packed__)) BasicLevelParamsPanel {
	char _unused_data_useless[0xC];

	struct TextMeshProUGUI* _durationText;
	struct TextMeshProUGUI* _bpmText;
} BasicLevelParamsPanel_t;
struct BetaBuildInfoText;
typedef struct __attribute__((__packed__)) BetaBuildInfoText {
	char _unused_data_useless[0xC];

	struct TextMeshProUGUI* _text;
} BetaBuildInfoText_t;
struct DifficultyTableCell;
typedef struct __attribute__((__packed__)) DifficultyTableCell {
	char _unused_data_useless[0x24];

	struct TextMeshProUGUI* _difficultyText;
	struct Image* _bgImage;
	struct Image* _highlightImage;
	void* _fillIndicator;
} DifficultyTableCell_t;
struct GameplayModifierInfoListItem;
typedef struct __attribute__((__packed__)) GameplayModifierInfoListItem {
	char _unused_data_useless[0xC];

	struct TextMeshProUGUI* _modifierNameText;
	struct TextMeshProUGUI* _modifierDescriptionText;
	struct Image* _iconImage;
	struct Image* _separatorImage;
} GameplayModifierInfoListItem_t;
struct LeaderboardTableCell;
typedef struct __attribute__((__packed__)) LeaderboardTableCell {
	char _unused_data_useless[0x24];

	struct TextMeshProUGUI* _rankText;
	struct TextMeshProUGUI* _playerNameText;
	struct TextMeshProUGUI* _scoreText;
	struct TextMeshProUGUI* _fullComboText;
	struct Color _normalColor;
	struct TMP_FontAsset* _normalFont;
	struct Color _specialScoreColor;
	struct TMP_FontAsset* _specialScoreFont;
	struct Image* _separatorImage;
} LeaderboardTableCell_t;
struct LevelListTableCell;
struct RawImage;
typedef struct __attribute__((__packed__)) RawImage {
	char _unused_data_useless[0x64];

	void* m_Texture;
	struct Rect m_UVRect;
} RawImage_t;
typedef struct __attribute__((__packed__)) LevelListTableCell {
	char _unused_data_useless[0x24];

	struct Color _selectedHighlightElementsColor;
	struct TextMeshProUGUI* _songNameText;
	struct TextMeshProUGUI* _authorText;
	struct RawImage* _coverRawImage;
	struct Image* _bgImage;
	struct Image* _highlightImage;
	struct Image* _beatmapCharacteristicImages;
	struct BeatmapCharacteristicSO* _beatmapCharacteristics;
	void* _refreshingAvailabilityCancellationTokenSource;
	void* _settingDataCancellationTokenSource;
	char _bought;
	cs_string* _refreshingAvailabilityLevelID;
	cs_string* _settingDataFromLevelId;
	void* _beatmapCharacteristicAlphas;
} LevelListTableCell_t;
struct LevelPackHeaderTableCell;
typedef struct __attribute__((__packed__)) LevelPackHeaderTableCell {
	char _unused_data_useless[0x24];

	struct Color _selectedHighlightElementsColor;
	struct TextMeshProUGUI* _nameText;
	struct Image* _bgImage;
	struct Image* _highlightImage;
	struct Image* _coverImage;
} LevelPackHeaderTableCell_t;
struct LevelPackTableCell;
typedef struct __attribute__((__packed__)) LevelPackTableCell {
	char _unused_data_useless[0x24];

	struct TextMeshProUGUI* _packNameText;
	struct TextMeshProUGUI* _infoText;
	struct Image* _coverImage;
	struct Image* _selectionImage;
	void* _newPromoRibbonObjects;
	void* _cancellationTokenSource;
} LevelPackTableCell_t;
struct LoadingControl;
typedef struct __attribute__((__packed__)) LoadingControl {
	char _unused_data_useless[0xC];

	void* _loadingIndicator;
	struct TextMeshProUGUI* _errorText;
	struct Button* _refreshButton;
	void* _errorContainer;
	void* _downloadingContainer;
	struct TextMeshProUGUI* _downloadingText;
	struct Image* _donwloadingProgressImage;
	void* didPressRefreshButtonEvent;
	struct ButtonBinder* _buttonBinder;
} LoadingControl_t;
struct MainSettingsTableCell;
typedef struct __attribute__((__packed__)) MainSettingsTableCell {
	char _unused_data_useless[0x24];

	struct TextMeshProUGUI* _settingsSubMenuText;
	struct Image* _bgImage;
	struct Image* _highlightImage;
} MainSettingsTableCell_t;
struct PackLevelListHeaderTableCell;
typedef struct __attribute__((__packed__)) PackLevelListHeaderTableCell {
	char _unused_data_useless[0x24];

	struct Color _selectedHighlightElementsColor;
	struct TextMeshProUGUI* _text;
	struct Image* _bgImage;
	struct Image* _highlightImage;
	struct Image* _arrowImage;
	void* _cancellationTokenSource;
} PackLevelListHeaderTableCell_t;
struct SimpleListTableCell;
typedef struct __attribute__((__packed__)) SimpleListTableCell {
	char _unused_data_useless[0x24];

	struct TextMeshProUGUI* _text;
	struct TextMeshProUGUI* _subText;
	struct Image* _bgImage;
	struct Image* _highlightImage;
	struct Image* _icon;
} SimpleListTableCell_t;
struct SimpleListTableView;
struct SimpleListTableItem;
typedef struct __attribute__((__packed__)) SimpleListTableItem {
	char _unused_data_useless[0x8];

	cs_string* text_k__BackingField;
	cs_string* subText_k__BackingField;
	struct Image* icon_k__BackingField;
	void* tag_k__BackingField;
} SimpleListTableItem_t;
typedef struct __attribute__((__packed__)) SimpleListTableView {
	char _unused_data_useless[0xC];

	struct TableView* _tableView;
	struct SimpleListTableCell* _cellPrefab;
	float _cellHeight;
	void* didSelectRow;
	struct SimpleListTableItem* _items;
} SimpleListTableView_t;
struct StartMiddleEndButtonBackgroundController;
typedef struct __attribute__((__packed__)) StartMiddleEndButtonBackgroundController {
	char _unused_data_useless[0xC];

	void* _startSprite;
	void* _middleSprite;
	void* _endSprite;
	struct Image* _image;
} StartMiddleEndButtonBackgroundController_t;
struct UIKeyboard;
typedef struct __attribute__((__packed__)) UIKeyboard {
	char _unused_data_useless[0xC];

	void* _keyButtonPrefab;
	void* textKeyWasPressedEvent;
	void* deleteButtonWasPressedEvent;
	void* okButtonWasPressedEvent;
	void* cancelButtonWasPressedEvent;
	struct Button* _okButton;
	struct Button* _cancelButton;
	char _okButtonInteractivity;
	char _hideCancelButton;
} UIKeyboard_t;
struct VRTextEntryController;
typedef struct __attribute__((__packed__)) VRTextEntryController {
	char _unused_data_useless[0xC];

	struct UIKeyboard* _uiKeyboard;
	struct TextMeshProUGUI* _text;
	struct TextMeshProUGUI* _cursorText;
	int _maxLength;
	char _allowBlank;
	void* textDidChangeEvent;
	void* okButtonWasPressedEvent;
	void* cancelButtonWasPressedEvent;
	char _stopBlinkingCursor;
} VRTextEntryController_t;
struct CreditsController;
typedef struct __attribute__((__packed__)) CreditsController {
	char _unused_data_useless[0xC];

	struct CreditsScenesTransitionSetupDataSO* _creditsSceneSetupDataSO;
	struct SongPreviewPlayer* _songPreviewPlayer;
	struct AudioClip* _creditsAudioClip;
	struct Button* _continueButton;
	void* _contentRectTransform;
	void* _textRectTransform;
	float _scrollingSpeed;
	float _overflowHeight;
	struct ButtonBinder* _buttonBinder;
	char _didFinish;
} CreditsController_t;
struct DismissableNavigationController;
typedef struct __attribute__((__packed__)) DismissableNavigationController {
	char _unused_data_useless[0x3C];

	struct Button* _backButton;
	void* didFinishEvent;
} DismissableNavigationController_t;
struct FileBrowserTableCell;
typedef struct __attribute__((__packed__)) FileBrowserTableCell {
	char _unused_data_useless[0x24];

	struct TextMeshProUGUI* _text;
	struct Image* _bgImage;
	struct Image* _highlightImage;
} FileBrowserTableCell_t;
struct FileBrowserTableView;
typedef struct __attribute__((__packed__)) FileBrowserTableView {
	char _unused_data_useless[0xC];

	struct TableView* _tableView;
	struct FileBrowserTableCell* _cellPrefab;
	float _cellHeight;
	void* didSelectRow;
	struct FileBrowserItem* _items;
} FileBrowserTableView_t;
struct ArcadeFlowCoordinator;
typedef struct __attribute__((__packed__)) ArcadeFlowCoordinator {
	char _unused_data_useless[0x44];

	struct MenuTransitionsHelperSO* _menuTransitionsHelper;
	struct LocalLeaderboardsModel* _localLeaderboardsModel;
	struct PlayerDataModelSO* _playerDataModel;
	struct BeatmapLevelsModelSO* _beatmapLevelsModelSO;
	struct MenuLightsPresetSO* _defaultLightsPreset;
	struct MenuLightsPresetSO* _resultsLightsPreset;
	struct VRUINavigationController* _navigationController;
	struct LevelPackLevelsViewController* _levelPackLevelsViewController;
	struct HowToPlayViewController* _howToPlayViewController;
	struct StandardLevelDetailViewController* _levelDetailViewController;
	struct PracticeViewController* _practiceViewController;
	struct ResultsViewController* _resultsViewController;
	struct EnterPlayerGuestNameViewController* _enterNameViewController;
	struct GameplaySetupViewController* _gameplaySetupViewController;
	struct LocalLeaderboardViewController* _localLeaderboardViewController;
	struct LevelPackDetailViewController* _levelPackDetailViewController;
	struct LevelPacksViewController* _levelPacksViewController;
	struct MenuLightsManager* _menuLightsManager;
	void* _levelPackCollection;
} ArcadeFlowCoordinator_t;
struct HealthWarningFlowCoordinator;
typedef struct __attribute__((__packed__)) HealthWarningFlowCoordinator {
	char _unused_data_useless[0x44];

	struct PlayerDataModelSO* _playerDataModel;
	struct Ease01* _fadeInOut;
	struct EulaViewController* _eulaViewController;
	struct HealthWarningViewController* _healthWarningViewContoller;
	struct ScenesTransitionSetupDataSO* _nextScenesTransitionSetupData;
} HealthWarningFlowCoordinator_t;
struct MainFlowCoordinator;
typedef struct __attribute__((__packed__)) MainFlowCoordinator {
	char _unused_data_useless[0x44];

	struct MenuTransitionsHelperSO* _menuTransitionsHelper;
	struct BeatmapLevelsModelSO* _beatmapLevelsModel;
	struct PlayerDataModelSO* _playerDataModel;
	struct MainSettingsModel* _mainSettingsModel;
	struct MenuLightsPresetSO* _defaultLightsPreset;
	struct Ease01* _fadeInOut;
	struct SoloFreePlayFlowCoordinator* _soloFreePlayFlowCoordinator;
	struct PartyFreePlayFlowCoordinator* _partyFreePlayFlowCoordinator;
	struct CampaignFlowCoordinator* _campaignFlowCoordinator;
	struct SettingsFlowCoordinator* _settingsFlowCoordinator;
	struct ReleaseInfoViewController* _releaseInfoViewController;
	struct SimpleDialogPromptViewController* _simpleDialogPromptViewController;
	struct MainMenuViewController* _mainMenuViewController;
	struct HowToPlayViewController* _howToPlayViewController;
	struct PlayerSettingsViewController* _playerSettingsViewController;
	struct PlayerStatisticsViewController* _playerStatisticsViewController;
	struct MenuLightsManager* _menuLightsManager;
	struct FlowCoordinator* _afterDialogPromptFlowCoordinator;
} MainFlowCoordinator_t;
struct PartyFreePlayFlowCoordinator;
typedef struct __attribute__((__packed__)) PartyFreePlayFlowCoordinator {
	char _unused_data_useless[0x44];

	struct MenuTransitionsHelperSO* _menuTransitionsHelper;
	struct LocalLeaderboardsModel* _localLeaderboardsModel;
	struct PlayerDataModelSO* _playerDataModel;
	struct BeatmapLevelsModelSO* _beatmapLevelsModelSO;
	struct MenuLightsPresetSO* _defaultLightsPreset;
	struct MenuLightsPresetSO* _resultsLightsPreset;
	struct DismissableNavigationController* _navigationController;
	struct StandardLevelDetailViewController* _levelDetailViewController;
	struct PracticeViewController* _practiceViewController;
	struct ResultsViewController* _resultsViewController;
	struct EnterPlayerGuestNameViewController* _enterNameViewController;
	struct GameplaySetupViewController* _gameplaySetupViewController;
	struct LocalLeaderboardViewController* _localLeaderboardViewController;
	struct LevelPackDetailViewController* _levelPackDetailViewController;
	struct LevelPackLevelsViewController* _levelPackLevelsViewController;
	struct LevelPacksViewController* _levelPacksViewController;
	struct MenuLightsManager* _menuLightsManager;
	void* _levelPackCollection;
	void* _loadPackCollectionCancellationTokenSource;
	char _levelPacksLoaded;
	void* didFinishEvent;
	void* didUpdateOverallStatsDataWithLevelCompletionResultsEvent;
} PartyFreePlayFlowCoordinator_t;
struct SettingsFlowCoordinator;
typedef struct __attribute__((__packed__)) SettingsFlowCoordinator {
	char _unused_data_useless[0x44];

	struct MainSettingsModel* _mainSettingsModel;
	struct MainSettingsMenuViewController* _mainSettingsMenuViewController;
	struct SettingsNavigationController* _settingsNavigationController;
	void* didFinishEvent;
} SettingsFlowCoordinator_t;
struct SimpleRetailDemoFlowCoordinator;
typedef struct __attribute__((__packed__)) SimpleRetailDemoFlowCoordinator {
	char _unused_data_useless[0x44];

	struct MenuTransitionsHelperSO* _menuTransitionsHelper;
	struct MenuLightsPresetSO* _defaultLightsPreset;
	struct Ease01* _fadeInOut;
	struct BeatmapLevelSO* _demoLevel1;
	struct BeatmapCharacteristicSO* _demoLevel1Characteristic;
	enum BeatmapDifficulty _demoLevel1Difficulty;
	struct BeatmapLevelSO* _demoLevel2;
	struct BeatmapCharacteristicSO* _demoLevel2Characteristic;
	enum BeatmapDifficulty _demoLevel2Difficulty;
	struct SimpleRetailDemoViewController* _simpleDemoViewController;
	struct HowToPlayViewController* _howToPlayViewController;
	struct ResultsViewController* _resultsViewController;
	struct MenuLightsManager* _menuLightsManager;
	void* _level1DifficultyBeatmap;
	void* _level2DifficultyBeatmap;
	void* _selectedLevelDifficultyBeatmap;
	char _quittingApplication;
} SimpleRetailDemoFlowCoordinator_t;
struct SoloFreePlayFlowCoordinator;
typedef struct __attribute__((__packed__)) SoloFreePlayFlowCoordinator {
	char _unused_data_useless[0x44];

	struct MenuTransitionsHelperSO* _menuTransitionsHelper;
	struct PlayerDataModelSO* _playerDataModel;
	struct PlatformLeaderboardsModel* _platformLeaderboardsModel;
	struct BeatmapLevelsModelSO* _beatmapLevelsModelSO;
	struct MenuLightsPresetSO* _defaultLightsPreset;
	struct MenuLightsPresetSO* _resultsLightsPreset;
	struct MenuLightsManager* _menuLightsManager;
	struct DismissableNavigationController* _navigationController;
	struct StandardLevelDetailViewController* _levelDetailViewController;
	struct PracticeViewController* _practiceViewController;
	struct ResultsViewController* _resultsViewController;
	struct GameplaySetupViewController* _gameplaySetupViewController;
	struct PlatformLeaderboardViewController* _platformLeaderboardViewController;
	struct LevelPacksViewController* _levelPacksViewController;
	struct LevelPackLevelsViewController* _levelPackLevelsViewController;
	struct LevelPackDetailViewController* _levelPackDetailViewController;
	void* didFinishEvent;
	void* didUpdateOverallStatsDataWithLevelCompletionResultsEvent;
	void* _levelPackCollection;
	void* _loadPackCollectionCancellationTokenSource;
	char _levelPacksLoaded;
} SoloFreePlayFlowCoordinator_t;
struct TestFlowCoordinator;
typedef struct __attribute__((__packed__)) TestFlowCoordinator {
	char _unused_data_useless[0x44];

	struct VRUIViewController* _viewController;
	struct VRUIViewController* _leftViewController;
	struct VRUIViewController* _rightViewController;
} TestFlowCoordinator_t;
struct GameplayModifierToggle;
typedef struct __attribute__((__packed__)) GameplayModifierToggle {
	char _unused_data_useless[0xC];

	struct GameplayModifierParamsSO* _gameplayModifier;
	struct TextMeshProUGUI* _nameText;
	struct HoverHint* _hoverHint;
	struct Image* _icon;
	struct Toggle* _toggle;
} GameplayModifierToggle_t;
struct GuestNameButtonsListItem;
typedef struct __attribute__((__packed__)) GuestNameButtonsListItem {
	char _unused_data_useless[0xC];

	struct TextMeshProUGUI* _nameText;
	struct Button* _button;
	void* _buttonPressed;
} GuestNameButtonsListItem_t;
struct HoverHint;
typedef struct __attribute__((__packed__)) HoverHint {
	char _unused_data_useless[0xC];

	cs_string* _text;
	struct Vector3 _worldCornersTemp;
	struct HoverHintController* _hoverHintController;
} HoverHint_t;
struct HoverHintController;
typedef struct __attribute__((__packed__)) HoverHintController {
	char _unused_data_useless[0xC];

	struct HoverHintPanel* _hoverHintPanelPrefab;
	struct HoverHintPanel* _hoverHintPanel;
	char _isHiding;
} HoverHintController_t;
struct HoverHintPanel;
typedef struct __attribute__((__packed__)) HoverHintPanel {
	char _unused_data_useless[0xC];

	struct TextMeshProUGUI* _text;
	struct Vector2 _padding;
	struct Vector2 _containerPadding;
	float _separator;
	float _zOffset;
	char isShown_k__BackingField;
} HoverHintPanel_t;
struct LeaderboardEntry;
typedef struct __attribute__((__packed__)) LeaderboardEntry {
	char _unused_data_useless[0xC];

	struct TextMeshProUGUI* _scoreText;
	struct TextMeshProUGUI* _playerNameText;
	struct TextMeshProUGUI* _rankText;
	struct Color _color;
} LeaderboardEntry_t;
struct LevelParamsPanel;
typedef struct __attribute__((__packed__)) LevelParamsPanel {
	char _unused_data_useless[0xC];

	struct TextMeshProUGUI* _durationText;
	struct TextMeshProUGUI* _bpmText;
	struct TextMeshProUGUI* _notesCountText;
	struct TextMeshProUGUI* _obstaclesCountText;
	struct TextMeshProUGUI* _bombsCountText;
} LevelParamsPanel_t;
struct MissionConnectionsGenerator;
typedef struct __attribute__((__packed__)) MissionConnectionsGenerator {
	char _unused_data_useless[0xC];

	struct MissionNodesManager* _missionNodesManager;
	struct MissionNodeConnection* _nodeConnectionPref;
	void* _connectionsCanvas;
	void* _missionNodes;
} MissionConnectionsGenerator_t;
struct MissionMapAnimationController;
typedef struct __attribute__((__packed__)) MissionMapAnimationController {
	char _unused_data_useless[0xC];

	struct MissionNodesManager* _missionNodesManager;
	struct ScrollView* _mapScrollView;
	float _startDelay;
	float _stageAnimationStartDelay;
	float _missionConnectionAnimationStartDelay;
	float _missionConnectionAnimationSeparationTime;
	float _stageAnimationDuration;
	struct ShockwaveEffect* _shockwaveEffect;
} MissionMapAnimationController_t;
struct MissionNodeGizmos;
typedef struct __attribute__((__packed__)) MissionNodeGizmos {
	char _unused_data_useless[0xC];

	struct MissionNode* _missionNode;
	struct CampaignProgressModelSO* _missionProgressModel;
	struct GameplayModifiersModelSO* _gameplayModifiersModel;
} MissionNodeGizmos_t;
struct MissionNodeVisualController;
typedef struct __attribute__((__packed__)) MissionNodeVisualController {
	char _unused_data_useless[0xC];

	struct MissionToggle* _missionToggle;
	struct MissionNode* _missionNode;
	void* nodeWasSelectEvent;
	void* nodeWasDisplayedEvent;
	char _selected;
	char _isInitialized;
	char _cleared;
	char _interactable;
} MissionNodeVisualController_t;
struct MissionStageLockView;
struct TMP_Text;
struct MaterialReference;
typedef struct __attribute__((__packed__)) MaterialReference {
	int index;
	struct TMP_FontAsset* fontAsset;
	struct TMP_SpriteAsset* spriteAsset;
	void* material;
	char isDefaultMaterial;
	char isFallbackMaterial;
	void* fallbackMaterial;
	float padding;
	int referenceCount;
} MaterialReference_t;
struct TMP_XmlTagStack_1;
typedef struct __attribute__((__packed__)) TMP_XmlTagStack_1 {
	void* itemStack;
	int index;
	int m_capacity;
	void* m_defaultItem;
} TMP_XmlTagStack_1_t;
struct Color32;
typedef struct __attribute__((__packed__)) Color32 {
	int rgba;
	char r;
	char g;
	char b;
	char a;
} Color32_t;
enum ColorMode {
	ColorMode_Single,
	ColorMode_HorizontalGradient,
	ColorMode_VerticalGradient,
	ColorMode_FourCornersGradient
};
struct VertexGradient;
typedef struct __attribute__((__packed__)) VertexGradient {
	struct Color topLeft;
	struct Color topRight;
	struct Color bottomLeft;
	struct Color bottomRight;
} VertexGradient_t;
struct TMP_ColorGradient;
typedef struct __attribute__((__packed__)) TMP_ColorGradient {
	char _unused_data_useless[0xC];

	enum ColorMode colorMode;
	struct Color topLeft;
	struct Color topRight;
	struct Color bottomLeft;
	struct Color bottomRight;
} TMP_ColorGradient_t;
enum FontStyles {
	FontStyles_Normal,
	FontStyles_Bold,
	FontStyles_Italic,
	FontStyles_Underline,
	FontStyles_LowerCase,
	FontStyles_UpperCase,
	FontStyles_SmallCaps,
	FontStyles_Strikethrough,
	FontStyles_Superscript,
	FontStyles_Subscript,
	FontStyles_Highlight
};
struct TMP_BasicXmlTagStack;
typedef struct __attribute__((__packed__)) TMP_BasicXmlTagStack {
	char bold;
	char italic;
	char underline;
	char strikethrough;
	char highlight;
	char superscript;
	char subscript;
	char uppercase;
	char lowercase;
	char smallcaps;
} TMP_BasicXmlTagStack_t;
enum TextAlignmentOptions {
	TextAlignmentOptions_TopLeft,
	TextAlignmentOptions_Top,
	TextAlignmentOptions_TopRight,
	TextAlignmentOptions_TopJustified,
	TextAlignmentOptions_TopFlush,
	TextAlignmentOptions_TopGeoAligned,
	TextAlignmentOptions_Left,
	TextAlignmentOptions_Center,
	TextAlignmentOptions_Right,
	TextAlignmentOptions_Justified,
	TextAlignmentOptions_Flush,
	TextAlignmentOptions_CenterGeoAligned,
	TextAlignmentOptions_BottomLeft,
	TextAlignmentOptions_Bottom,
	TextAlignmentOptions_BottomRight,
	TextAlignmentOptions_BottomJustified,
	TextAlignmentOptions_BottomFlush,
	TextAlignmentOptions_BottomGeoAligned,
	TextAlignmentOptions_BaselineLeft,
	TextAlignmentOptions_Baseline,
	TextAlignmentOptions_BaselineRight,
	TextAlignmentOptions_BaselineJustified,
	TextAlignmentOptions_BaselineFlush,
	TextAlignmentOptions_BaselineGeoAligned,
	TextAlignmentOptions_MidlineLeft,
	TextAlignmentOptions_Midline,
	TextAlignmentOptions_MidlineRight,
	TextAlignmentOptions_MidlineJustified,
	TextAlignmentOptions_MidlineFlush,
	TextAlignmentOptions_MidlineGeoAligned,
	TextAlignmentOptions_CaplineLeft,
	TextAlignmentOptions_Capline,
	TextAlignmentOptions_CaplineRight,
	TextAlignmentOptions_CaplineJustified,
	TextAlignmentOptions_CaplineFlush,
	TextAlignmentOptions_CaplineGeoAligned
};
enum TextOverflowModes {
	TextOverflowModes_Overflow,
	TextOverflowModes_Ellipsis,
	TextOverflowModes_Masking,
	TextOverflowModes_Truncate,
	TextOverflowModes_ScrollRect,
	TextOverflowModes_Page,
	TextOverflowModes_Linked
};
enum TextureMappingOptions {
	TextureMappingOptions_Character,
	TextureMappingOptions_Line,
	TextureMappingOptions_Paragraph,
	TextureMappingOptions_MatchAspect
};
enum TextRenderFlags {
	TextRenderFlags_DontRender,
	TextRenderFlags_Render
};
enum VertexSortingOrder {
	VertexSortingOrder_Normal,
	VertexSortingOrder_Reverse
};
struct TMP_TextInfo;
struct TMP_CharacterInfo;
enum TMP_TextElementType {
	TMP_TextElementType_Character,
	TMP_TextElementType_Sprite
};
struct TMP_TextElement;
typedef struct __attribute__((__packed__)) TMP_TextElement {
	char _unused_data_useless[0x8];

	int id;
	float x;
	float y;
	float width;
	float height;
	float xOffset;
	float yOffset;
	float xAdvance;
	float scale;
} TMP_TextElement_t;
struct TMP_Vertex;
typedef struct __attribute__((__packed__)) TMP_Vertex {
	struct Vector3 position;
	struct Vector2 uv;
	struct Vector2 uv2;
	struct Vector2 uv4;
	struct Color32 color;
} TMP_Vertex_t;
typedef struct __attribute__((__packed__)) TMP_CharacterInfo {
	char character;
	int index;
	enum TMP_TextElementType elementType;
	struct TMP_TextElement* textElement;
	struct TMP_FontAsset* fontAsset;
	struct TMP_SpriteAsset* spriteAsset;
	int spriteIndex;
	void* material;
	int materialReferenceIndex;
	char isUsingAlternateTypeface;
	float pointSize;
	int lineNumber;
	int pageNumber;
	int vertexIndex;
	struct TMP_Vertex vertex_TL;
	struct TMP_Vertex vertex_BL;
	struct TMP_Vertex vertex_TR;
	struct TMP_Vertex vertex_BR;
	struct Vector3 topLeft;
	struct Vector3 bottomLeft;
	struct Vector3 topRight;
	struct Vector3 bottomRight;
	float origin;
	float ascender;
	float baseLine;
	float descender;
	float xAdvance;
	float aspectRatio;
	float scale;
	struct Color32 color;
	struct Color32 underlineColor;
	struct Color32 strikethroughColor;
	struct Color32 highlightColor;
	enum FontStyles style;
	char isVisible;
} TMP_CharacterInfo_t;
struct TMP_WordInfo;
typedef struct __attribute__((__packed__)) TMP_WordInfo {
	struct TMP_Text* textComponent;
	int firstCharacterIndex;
	int lastCharacterIndex;
	int characterCount;
} TMP_WordInfo_t;
struct TMP_LinkInfo;
typedef struct __attribute__((__packed__)) TMP_LinkInfo {
	struct TMP_Text* textComponent;
	int hashCode;
	int linkIdFirstCharacterIndex;
	int linkIdLength;
	int linkTextfirstCharacterIndex;
	int linkTextLength;
	void* linkID;
} TMP_LinkInfo_t;
struct TMP_LineInfo;
struct Extents;
typedef struct __attribute__((__packed__)) Extents {
	struct Vector2 min;
	struct Vector2 max;
} Extents_t;
typedef struct __attribute__((__packed__)) TMP_LineInfo {
	int controlCharacterCount;
	int characterCount;
	int visibleCharacterCount;
	int spaceCount;
	int wordCount;
	int firstCharacterIndex;
	int firstVisibleCharacterIndex;
	int lastCharacterIndex;
	int lastVisibleCharacterIndex;
	float length;
	float lineHeight;
	float ascender;
	float baseline;
	float descender;
	float maxAdvance;
	float width;
	float marginLeft;
	float marginRight;
	enum TextAlignmentOptions alignment;
	struct Extents lineExtents;
} TMP_LineInfo_t;
struct TMP_PageInfo;
typedef struct __attribute__((__packed__)) TMP_PageInfo {
	int firstCharacterIndex;
	int lastCharacterIndex;
	float ascender;
	float baseLine;
	float descender;
} TMP_PageInfo_t;
struct TMP_MeshInfo;
typedef struct __attribute__((__packed__)) TMP_MeshInfo {
	void* mesh;
	int vertexCount;
	struct Vector3 vertices;
	struct Vector3 normals;
	struct Vector4 tangents;
	struct Vector2 uvs0;
	struct Vector2 uvs2;
	struct Color32 colors32;
	void* triangles;
} TMP_MeshInfo_t;
typedef struct __attribute__((__packed__)) TMP_TextInfo {
	char _unused_data_useless[0x8];

	struct TMP_Text* textComponent;
	int characterCount;
	int spriteCount;
	int spaceCount;
	int wordCount;
	int linkCount;
	int lineCount;
	int pageCount;
	int materialCount;
	struct TMP_CharacterInfo characterInfo;
	struct TMP_WordInfo wordInfo;
	struct TMP_LinkInfo linkInfo;
	struct TMP_LineInfo lineInfo;
	struct TMP_PageInfo pageInfo;
	struct TMP_MeshInfo meshInfo;
	struct TMP_MeshInfo m_CachedMeshInfo;
} TMP_TextInfo_t;
struct TMP_SpriteAnimator;
typedef struct __attribute__((__packed__)) TMP_SpriteAnimator {
	char _unused_data_useless[0xC];

	void* m_animations;
	struct TMP_Text* m_TextComponent;
} TMP_SpriteAnimator_t;
struct LayoutElement;
typedef struct __attribute__((__packed__)) LayoutElement {
	char _unused_data_useless[0xC];

	char m_IgnoreLayout;
	float m_MinWidth;
	float m_MinHeight;
	float m_PreferredWidth;
	float m_PreferredHeight;
	float m_FlexibleWidth;
	float m_FlexibleHeight;
	int m_LayoutPriority;
} LayoutElement_t;
enum TextInputSources {
	TextInputSources_Text,
	TextInputSources_SetText,
	TextInputSources_SetCharArray,
	TextInputSources_String
};
struct XML_TagAttribute;
enum TagType {
	TagType_None,
	TagType_NumericalValue,
	TagType_StringValue,
	TagType_ColorValue
};
typedef struct __attribute__((__packed__)) XML_TagAttribute {
	int nameHashCode;
	enum TagType valueType;
	int valueStartIndex;
	int valueLength;
	int valueHashCode;
} XML_TagAttribute_t;
struct WordWrapState;
typedef struct __attribute__((__packed__)) WordWrapState {
	int previous_WordBreak;
	int total_CharacterCount;
	int visible_CharacterCount;
	int visible_SpriteCount;
	int visible_LinkCount;
	int firstCharacterIndex;
	int firstVisibleCharacterIndex;
	int lastCharacterIndex;
	int lastVisibleCharIndex;
	int lineNumber;
	float maxCapHeight;
	float maxAscender;
	float maxDescender;
	float maxLineAscender;
	float maxLineDescender;
	float previousLineAscender;
	float xAdvance;
	float preferredWidth;
	float preferredHeight;
	float previousLineScale;
	int wordCount;
	enum FontStyles fontStyle;
	float fontScale;
	float fontScaleMultiplier;
	float currentFontSize;
	float baselineOffset;
	float lineOffset;
	struct TMP_TextInfo* textInfo;
	struct TMP_LineInfo lineInfo;
	struct Color32 vertexColor;
	struct Color32 underlineColor;
	struct Color32 strikethroughColor;
	struct Color32 highlightColor;
	struct TMP_BasicXmlTagStack basicStyleStack;
	void* colorStack;
	void* underlineColorStack;
	void* strikethroughColorStack;
	void* highlightColorStack;
	void* colorGradientStack;
	void* sizeStack;
	void* indentStack;
	void* fontWeightStack;
	void* styleStack;
	void* baselineStack;
	void* actionStack;
	void* materialReferenceStack;
	void* lineJustificationStack;
	int spriteAnimationID;
	struct TMP_FontAsset* currentFontAsset;
	struct TMP_SpriteAsset* currentSpriteAsset;
	void* currentMaterial;
	int currentMaterialIndex;
	struct Extents meshExtents;
	char tagNoParsing;
	char isNonBreakingSpace;
} WordWrapState_t;
typedef struct __attribute__((__packed__)) TMP_Text {
	char _unused_data_useless[0x64];

	cs_string* m_text;
	char m_isRightToLeft;
	struct TMP_FontAsset* m_fontAsset;
	struct TMP_FontAsset* m_currentFontAsset;
	char m_isSDFShader;
	void* m_sharedMaterial;
	void* m_currentMaterial;
	struct MaterialReference m_materialReferences;
	void* m_materialReferenceIndexLookup;
	void* m_materialReferenceStack;
	int m_currentMaterialIndex;
	void* m_fontSharedMaterials;
	void* m_fontMaterial;
	void* m_fontMaterials;
	char m_isMaterialDirty;
	struct Color32 m_fontColor32;
	struct Color m_fontColor;
	struct Color32 m_underlineColor;
	struct Color32 m_strikethroughColor;
	struct Color32 m_highlightColor;
	char m_enableVertexGradient;
	enum ColorMode m_colorMode;
	struct VertexGradient m_fontColorGradient;
	struct TMP_ColorGradient* m_fontColorGradientPreset;
	struct TMP_SpriteAsset* m_spriteAsset;
	char m_tintAllSprites;
	char m_tintSprite;
	struct Color32 m_spriteColor;
	char m_overrideHtmlColors;
	struct Color32 m_faceColor;
	struct Color32 m_outlineColor;
	float m_outlineWidth;
	float m_fontSize;
	float m_currentFontSize;
	float m_fontSizeBase;
	void* m_sizeStack;
	int m_fontWeight;
	int m_fontWeightInternal;
	void* m_fontWeightStack;
	char m_enableAutoSizing;
	float m_maxFontSize;
	float m_minFontSize;
	float m_fontSizeMin;
	float m_fontSizeMax;
	enum FontStyles m_fontStyle;
	enum FontStyles m_style;
	struct TMP_BasicXmlTagStack m_fontStyleStack;
	char m_isUsingBold;
	enum TextAlignmentOptions m_textAlignment;
	enum TextAlignmentOptions m_lineJustification;
	void* m_lineJustificationStack;
	struct Vector3 m_textContainerLocalCorners;
	char m_isAlignmentEnumConverted;
	float m_characterSpacing;
	float m_cSpacing;
	float m_monoSpacing;
	float m_wordSpacing;
	float m_lineSpacing;
	float m_lineSpacingDelta;
	float m_lineHeight;
	float m_lineSpacingMax;
	float m_paragraphSpacing;
	float m_charWidthMaxAdj;
	float m_charWidthAdjDelta;
	char m_enableWordWrapping;
	char m_isCharacterWrappingEnabled;
	char m_isNonBreakingSpace;
	char m_isIgnoringAlignment;
	float m_wordWrappingRatios;
	enum TextOverflowModes m_overflowMode;
	int m_firstOverflowCharacterIndex;
	struct TMP_Text* m_linkedTextComponent;
	char m_isLinkedTextComponent;
	char m_isTextTruncated;
	char m_enableKerning;
	char m_enableExtraPadding;
	char checkPaddingRequired;
	char m_isRichText;
	char m_parseCtrlCharacters;
	char m_isOverlay;
	char m_isOrthographic;
	char m_isCullingEnabled;
	char m_ignoreRectMaskCulling;
	char m_ignoreCulling;
	enum TextureMappingOptions m_horizontalMapping;
	enum TextureMappingOptions m_verticalMapping;
	float m_uvLineOffset;
	enum TextRenderFlags m_renderMode;
	enum VertexSortingOrder m_geometrySortingOrder;
	int m_firstVisibleCharacter;
	int m_maxVisibleCharacters;
	int m_maxVisibleWords;
	int m_maxVisibleLines;
	char m_useMaxVisibleDescender;
	int m_pageToDisplay;
	char m_isNewPage;
	struct Vector4 m_margin;
	float m_marginLeft;
	float m_marginRight;
	float m_marginWidth;
	float m_marginHeight;
	float m_width;
	struct TMP_TextInfo* m_textInfo;
	char m_havePropertiesChanged;
	char m_isUsingLegacyAnimationComponent;
	void* m_transform;
	void* m_rectTransform;
	char autoSizeTextContainer_k__BackingField;
	char m_autoSizeTextContainer;
	void* m_mesh;
	char m_isVolumetricText;
	struct TMP_SpriteAnimator* m_spriteAnimator;
	float m_flexibleHeight;
	float m_flexibleWidth;
	float m_minWidth;
	float m_minHeight;
	float m_maxWidth;
	float m_maxHeight;
	struct LayoutElement* m_LayoutElement;
	float m_preferredWidth;
	float m_renderedWidth;
	char m_isPreferredWidthDirty;
	float m_preferredHeight;
	float m_renderedHeight;
	char m_isPreferredHeightDirty;
	char m_isCalculatingPreferredValues;
	int m_recursiveCount;
	int m_layoutPriority;
	char m_isCalculateSizeRequired;
	char m_isLayoutDirty;
	char m_verticesAlreadyDirty;
	char m_layoutAlreadyDirty;
	char m_isAwake;
	char m_isWaitingOnResourceLoad;
	char m_isInputParsingRequired;
	enum TextInputSources m_inputSource;
	cs_string* old_text;
	float m_fontScale;
	float m_fontScaleMultiplier;
	void* m_htmlTag;
	struct XML_TagAttribute m_xmlAttribute;
	void* m_attributeParameterValues;
	float tag_LineIndent;
	float tag_Indent;
	void* m_indentStack;
	char tag_NoParsing;
	char m_isParsingText;
	struct Matrix4x4 m_FXMatrix;
	char m_isFXMatrixSet;
	void* m_char_buffer;
	struct TMP_CharacterInfo m_internalCharacterInfo;
	void* m_input_CharArray;
	int m_charArray_Length;
	int m_totalCharacterCount;
	struct WordWrapState m_SavedWordWrapState;
	struct WordWrapState m_SavedLineState;
	int m_characterCount;
	int m_firstCharacterOfLine;
	int m_firstVisibleCharacterOfLine;
	int m_lastCharacterOfLine;
	int m_lastVisibleCharacterOfLine;
	int m_lineNumber;
	int m_lineVisibleCharacterCount;
	int m_pageNumber;
	float m_maxAscender;
	float m_maxCapHeight;
	float m_maxDescender;
	float m_maxLineAscender;
	float m_maxLineDescender;
	float m_startOfLineAscender;
	float m_lineOffset;
	struct Extents m_meshExtents;
	struct Color32 m_htmlColor;
	void* m_colorStack;
	void* m_underlineColorStack;
	void* m_strikethroughColorStack;
	void* m_highlightColorStack;
	struct TMP_ColorGradient* m_colorGradientPreset;
	void* m_colorGradientStack;
	float m_tabSpacing;
	float m_spacing;
	void* m_styleStack;
	void* m_actionStack;
	float m_padding;
	float m_baselineOffset;
	void* m_baselineOffsetStack;
	float m_xAdvance;
	enum TMP_TextElementType m_textElementType;
	struct TMP_TextElement* m_cached_TextElement;
	void* m_cached_Underline_GlyphInfo;
	void* m_cached_Ellipsis_GlyphInfo;
	struct TMP_SpriteAsset* m_defaultSpriteAsset;
	struct TMP_SpriteAsset* m_currentSpriteAsset;
	int m_spriteCount;
	int m_spriteIndex;
	int m_spriteAnimationID;
	char m_ignoreActiveState;
	void* k_Power;
} TMP_Text_t;
typedef struct __attribute__((__packed__)) MissionStageLockView {
	char _unused_data_useless[0xC];

	struct TMP_Text* _text;
	void* _rectTransform;
	float _dstPosY;
	float _animationDuration;
	float _startAnimationTime;
} MissionStageLockView_t;
struct MissionToggle;
typedef struct __attribute__((__packed__)) MissionToggle {
	char _unused_data_useless[0xC];

	struct Signal* _missionToggleWasPressedSignal;
	struct TextMeshProUGUI* _text;
	struct Image* _lockedImage;
	struct Image* _clearedImage;
	struct Image* _bgImage;
	struct Image* _strokeImage;
	struct Image* _strokeGlowImage;
	struct VRInteractable* _vrInteractable;
	struct Color _disabledColor;
	struct Color _normalColor;
	struct Color _invertColor;
	struct Color _highlightColor;
	void* selectionDidChangeEvent;
	char _selected;
	char _highlighted;
	char _interactable;
	char _missionCleared;
} MissionToggle_t;
struct ObjectiveListItem;
typedef struct __attribute__((__packed__)) ObjectiveListItem {
	char _unused_data_useless[0xC];

	struct TextMeshProUGUI* _titleText;
	struct TextMeshProUGUI* _conditionText;
} ObjectiveListItem_t;
struct ResultObjectiveListItem;
typedef struct __attribute__((__packed__)) ResultObjectiveListItem {
	char _unused_data_useless[0xC];

	struct Image* _icon;
	struct Image* _iconGlow;
	struct TextMeshProUGUI* _titleText;
	struct TextMeshProUGUI* _conditionText;
	struct TextMeshProUGUI* _valueText;
} ResultObjectiveListItem_t;
struct ScrollViewItemsVisibilityController;
typedef struct __attribute__((__packed__)) ScrollViewItemsVisibilityController {
	char _unused_data_useless[0xC];

	void* _viewport;
	void* _contentRectTransform;
	void* _items;
	float _lastContentAnchoredPositionY;
	struct Vector3 _viewportWorldCorners;
	void* _upperItemsCornes;
	void* _lowerItemsCornes;
	int _lowerLastVisibleIndex;
	int _upperLastVisibleIndex;
	float _contentMaxY;
	float _contentMinY;
} ScrollViewItemsVisibilityController_t;
struct SetMainCameraToCanvas;
typedef struct __attribute__((__packed__)) SetMainCameraToCanvas {
	char _unused_data_useless[0xC];

	void* _canvas;
	struct MainCamera* _mainCamera;
} SetMainCameraToCanvas_t;
struct BoolSettingsController;
typedef struct __attribute__((__packed__)) BoolSettingsController {
	char _unused_data_useless[0x1C];

	void* _settingsValue;
	cs_string* _onText;
	cs_string* _offText;
} BoolSettingsController_t;
struct FormattedFloatListSettingsController;
enum ValueType {
	ValueType_Normal,
	ValueType_Normalized,
	ValueType_InvertedNormalized
};
typedef struct __attribute__((__packed__)) FormattedFloatListSettingsController {
	char _unused_data_useless[0x20];

	void* _settingsValue;
	void* _values;
	cs_string* _formattingString;
	enum ValueType valueType;
	float _min;
	float _max;
} FormattedFloatListSettingsController_t;
struct PresetsSettingsController;
typedef struct __attribute__((__packed__)) PresetsSettingsController {
	char _unused_data_useless[0x20];

	void* _settingsValue;
	void* _presets;
} PresetsSettingsController_t;
struct PlayerHeightSettingsController;
typedef struct __attribute__((__packed__)) PlayerHeightSettingsController {
	char _unused_data_useless[0xC];

	struct TextMeshProUGUI* _text;
	struct Button* _resetButton;
	struct Button* _setButton;
	void* _roomCenter;
	struct PlayerSpecificSettings* _playerSettings;
	struct ButtonBinder* _buttonBinder;
} PlayerHeightSettingsController_t;
struct SmoothCameraSmoothnessSettingsController;
typedef struct __attribute__((__packed__)) SmoothCameraSmoothnessSettingsController {
	char _unused_data_useless[0x20];

	void* _smoothCameraPositionSmooth;
	void* _smoothCameraRotationSmooth;
	void* _smoothnesses;
} SmoothCameraSmoothnessSettingsController_t;
struct WindowResolutionSettingsController;
struct Vector2Int;
typedef struct __attribute__((__packed__)) Vector2Int {
	int m_X;
	int m_Y;
} Vector2Int_t;
typedef struct __attribute__((__packed__)) WindowResolutionSettingsController {
	char _unused_data_useless[0x20];

	void* _windowResolution;
	struct Vector2Int _windowResolutions;
} WindowResolutionSettingsController_t;
struct TextAndImageTableCell;
typedef struct __attribute__((__packed__)) TextAndImageTableCell {
	char _unused_data_useless[0x24];

	struct TextMeshProUGUI* _text;
	struct Image* _bgImage;
	struct Image* _image;
	struct Color _highlightBGColor;
	struct Color _selectBGColor;
	struct Color _defaultBGColor;
	struct Color _highlightColor;
	struct Color _selectColor;
	struct Color _defaultColor;
} TextAndImageTableCell_t;
struct TextureRawImageLoader;
struct StackTextureLoaderSO;
struct CancelableTextureLoader;
typedef struct __attribute__((__packed__)) CancelableTextureLoader {
	char _unused_data_useless[0x8];

	char finishedLoading_k__BackingField;
	char _loadingCanceled;
	void* _finishedCallback;
	cs_string* _filePath;
} CancelableTextureLoader_t;
typedef struct __attribute__((__packed__)) StackTextureLoaderSO {
	char _unused_data_useless[0xC];

	void* _textureLoaderStack;
	struct CancelableTextureLoader* _currentTextureLoader;
	char _running;
} StackTextureLoaderSO_t;
typedef struct __attribute__((__packed__)) TextureRawImageLoader {
	char _unused_data_useless[0xC];

	struct StackTextureLoaderSO* _stackTextureLoaderSO;
	struct RawImage* _rawImage;
	cs_string* _imageTexturePath;
	void* _cancelableTextureLoader;
} TextureRawImageLoader_t;
struct AddGuestPlayerViewController;
typedef struct __attribute__((__packed__)) AddGuestPlayerViewController {
	char _unused_data_useless[0x34];

	struct VRTextEntryController* _textEntryController;
	void* _infoPanel;
	struct TextMeshProUGUI* _infoText;
	struct Button* _okButton;
	struct Button* _cancelButton;
	void* didFinishEvent;
	struct PlayerDataModelSO* _playerDataModel;
} AddGuestPlayerViewController_t;
struct AudioLatencyViewController;
typedef struct __attribute__((__packed__)) AudioLatencyViewController {
	char _unused_data_useless[0x34];

	void* _audioLatency;
	struct TextScrollbar* _scrollbar;
	struct VisualMetronome* _visualMetronome;
	float _bufferLatency;
} AudioLatencyViewController_t;
struct BeatmapCharacteristicSegmentedControlController;
typedef struct __attribute__((__packed__)) BeatmapCharacteristicSegmentedControlController {
	char _unused_data_useless[0xC];

	struct IconSegmentedControl* _segmentedControl;
	void* didSelectBeatmapCharacteristicEvent;
	struct BeatmapCharacteristicSO* _selectedBeatmapCharacteristic;
	void* _beatmapCharacteristics;
} BeatmapCharacteristicSegmentedControlController_t;
struct BeatmapCharacteristicSelectionViewController;
typedef struct __attribute__((__packed__)) BeatmapCharacteristicSelectionViewController {
	char _unused_data_useless[0x34];

	struct IconSegmentedControl* _beatmapCharacteristicSegmentedControl;
	void* _beatmapCharacteristicCollection;
	void* didSelectBeatmapCharacteristicEvent;
	struct BeatmapCharacteristicSO* _selectedBeatmapCharacteristic;
} BeatmapCharacteristicSelectionViewController_t;
struct BeatmapDifficultySegmentedControlController;
typedef struct __attribute__((__packed__)) BeatmapDifficultySegmentedControlController {
	char _unused_data_useless[0xC];

	struct TextSegmentedControl* _difficultySegmentedControl;
	void* didSelectDifficultyEvent;
	void* _difficulties;
	enum BeatmapDifficulty _selectedDifficulty;
} BeatmapDifficultySegmentedControlController_t;
struct BeatmapDifficultyViewController;
typedef struct __attribute__((__packed__)) BeatmapDifficultyViewController {
	char _unused_data_useless[0x34];

	struct DifficultyTableView* _difficultyTableView;
	void* _blockingUI;
	void* didSelectDifficultyEvent;
	void* _difficultyBeatmaps;
	void* _selectedDifficultyBeatmap;
} BeatmapDifficultyViewController_t;
struct CrashInfoViewController;
struct CrashManagerSO;
typedef struct __attribute__((__packed__)) CrashManagerSO {
	char _unused_data_useless[0xC];

	cs_string* _logString;
	cs_string* _stackTrace;
} CrashManagerSO_t;
typedef struct __attribute__((__packed__)) CrashInfoViewController {
	char _unused_data_useless[0xC];

	struct CrashManagerSO* _crashManager;
	struct TextMeshProUGUI* _text;
} CrashInfoViewController_t;
struct EnterPlayerGuestNameViewController;
typedef struct __attribute__((__packed__)) EnterPlayerGuestNameViewController {
	char _unused_data_useless[0x34];

	struct PlayerDataModelSO* _playerDataModel;
	struct VRTextEntryController* _textEntryController;
	void* _guestNameButtonsListItemsList;
	void* _didFinishCallback;
} EnterPlayerGuestNameViewController_t;
struct EnterTextViewController;
typedef struct __attribute__((__packed__)) EnterTextViewController {
	char _unused_data_useless[0x34];

	struct VRTextEntryController* _textEntryController;
	struct TextMeshProUGUI* _titleText;
	struct Button* _okButton;
	void* didFinishEvent;
} EnterTextViewController_t;
struct EulaViewController;
typedef struct __attribute__((__packed__)) EulaViewController {
	char _unused_data_useless[0x34];

	struct Button* _agreeButton;
	struct Button* _doNotAgreeButton;
	struct TextPageScrollView* _textPageScrollView;
	void* _eulaTextAsset;
	void* didFinishEvent;
} EulaViewController_t;
struct FloorAdjustViewController;
typedef struct __attribute__((__packed__)) FloorAdjustViewController {
	char _unused_data_useless[0x34];

	void* _roomCenter;
	struct Button* _yIncButton;
	struct Button* _yDecButton;
	struct TextMeshProUGUI* _playerHeightText;
	float _playerHeight;
} FloorAdjustViewController_t;
struct GameplayModifiersPanelController;
struct ToggleBinder;
typedef struct __attribute__((__packed__)) ToggleBinder {
	char _unused_data_useless[0x8];

	void* _bindings;
	char _enabled;
} ToggleBinder_t;
typedef struct __attribute__((__packed__)) GameplayModifiersPanelController {
	char _unused_data_useless[0xC];

	struct GameplayModifiersModelSO* _gameplayModifiersModel;
	struct TextMeshProUGUI* _totalMultiplierValueText;
	struct TextMeshProUGUI* _maxRankValueText;
	struct GameplayModifiers* _gameplayModifiers;
	struct ToggleBinder* _toggleBinder;
	struct GameplayModifierToggle* _gameplayModifierToggles;
	char _changingGameplayModifierToggles;
} GameplayModifiersPanelController_t;
struct GameplaySetupViewController;
typedef struct __attribute__((__packed__)) GameplaySetupViewController {
	char _unused_data_useless[0x34];

	struct TextSegmentedControl* _selectionSegmentedControl;
	struct PlayerSettingsPanelController* _playerSettingsPanelController;
	struct GameplayModifiersPanelController* _gameplayModifiersPanelController;
	void* changePlayerButtonPressedEvent;
	void* _panels;
} GameplaySetupViewController_t;
struct PlayerSettingsPanelController;
typedef struct __attribute__((__packed__)) PlayerSettingsPanelController {
	char _unused_data_useless[0xC];

	struct ColorManager* _colorManager;
	struct Toggle* _leftHandedToggle;
	struct Toggle* _swapColorsToggle;
	struct Toggle* _staticLightsToggle;
	struct Toggle* _disableSFXToggle;
	struct Toggle* _reduceDebrisToggle;
	struct Toggle* _noTextsAndHudsToggle;
	struct Toggle* _advanceHudToggle;
	struct Toggle* _autoRestartToggle;
	struct PlayerHeightSettingsController* _playerHeightSettingsController;
	struct PlayerSpecificSettings* _playerSpecificSettings;
	struct ToggleBinder* _toggleBinder;
} PlayerSettingsPanelController_t;
struct PlayerSettingsViewController;
typedef struct __attribute__((__packed__)) PlayerSettingsViewController {
	char _unused_data_useless[0x34];

	struct PlayerDataModelSO* _playerDataModelSO;
	struct PlayerSettingsPanelController* _playerSettingsPanelController;
	struct Button* _backButton;
	void* _backButtonContainer;
	char _hideBackButton;
	void* didFinishEvent;
} PlayerSettingsViewController_t;
struct HealthWarningViewController;
typedef struct __attribute__((__packed__)) HealthWarningViewController {
	char _unused_data_useless[0x34];

	struct Button* _continueButton;
	void* didFinishEvent;
} HealthWarningViewController_t;
struct HowToPlayViewController;
typedef struct __attribute__((__packed__)) HowToPlayViewController {
	char _unused_data_useless[0x34];

	struct Button* _tutorialButton;
	struct Button* _backButton;
	struct TextSegmentedControl* _selectionSegmentedControl;
	void* _panels;
	void* didPressTutorialButtonEvent;
	void* didFinishEvent;
} HowToPlayViewController_t;
struct LevelPackDetailViewController;
struct EventBinder;
typedef struct __attribute__((__packed__)) EventBinder {
	char _unused_data_useless[0x8];

	void* _unsubscribes;
} EventBinder_t;
typedef struct __attribute__((__packed__)) LevelPackDetailViewController {
	char _unused_data_useless[0x34];

	void* _detailWrapper;
	struct Image* _packImage;
	struct Button* _buyButton;
	void* _buyContainer;
	struct LoadingControl* _loadingControl;
	struct AdditionalContentModelSO* _additionalContentModel;
	struct EventBinder* _eventBinder;
	void* _cancellationTokenSource;
	void* _pack;
} LevelPackDetailViewController_t;
struct LevelPackLevelsViewController;
typedef struct __attribute__((__packed__)) LevelPackLevelsViewController {
	char _unused_data_useless[0x34];

	struct LevelPackLevelsTableView* _levelPackLevelsTableView;
	struct AdditionalContentModelSO* _additionalContentModel;
	struct SongPreviewPlayer* _songPreviewPlayer;
	void* didSelectLevelEvent;
	void* didSelectPackEvent;
	void* _levelPack;
	char _showLevelPackHeader;
	void* _cancellationTokenSource;
	cs_string* _songPlayerCrossfadignToLevelId;
} LevelPackLevelsViewController_t;
struct LevelPacksViewController;
typedef struct __attribute__((__packed__)) LevelPacksViewController {
	char _unused_data_useless[0x34];

	struct LevelPacksTableView* _levelPacksTableView;
	struct AdditionalContentModelSO* _additionalContentModel;
	void* didSelectPackEvent;
	void* _levelPackCollection;
	int _selectedPackNum;
} LevelPacksViewController_t;
struct LocalLeaderboardViewController;
struct NoTransitionsButton;
enum SelectionState {
	SelectionState_Normal,
	SelectionState_Highlighted,
	SelectionState_Pressed,
	SelectionState_Disabled
};
typedef struct __attribute__((__packed__)) NoTransitionsButton {
	char _unused_data_useless[0x98];

	void* selectionStateDidChangeEvent;
	enum SelectionState _selectionState;
} NoTransitionsButton_t;
typedef struct __attribute__((__packed__)) LocalLeaderboardViewController {
	char _unused_data_useless[0x34];

	int _maxNumberOfCells;
	struct LocalLeaderboardsModel* _localLeaderboardsModel;
	struct PlayerDataModelSO* _playerDataModel;
	void* _leaderboardTableView;
	void* _clearLeaderboardsWrapper;
	struct NoTransitionsButton* _clearLeaderboardsButton;
	struct IconSegmentedControl* _scopeSegmentedControl;
	void* _allTimeLeaderboardIcon;
	void* _todayLeaderboardIcon;
	void* _clearLeaderboardIcon;
	void* _difficultyBeatmap;
	char _refreshIsNeeded;
} LocalLeaderboardViewController_t;
struct MainMenuViewController;
typedef struct __attribute__((__packed__)) MainMenuViewController {
	char _unused_data_useless[0x34];

	struct Button* _soloButton;
	struct Button* _partyButton;
	struct Button* _campaignButton;
	struct Button* _settingsButton;
	struct Button* _playerSettingsButton;
	struct Button* _quitButton;
	struct Button* _howToPlayButton;
	struct Button* _beatmapEditorButton;
	struct Button* _creditsButton;
	void* didFinishEvent;
} MainMenuViewController_t;
struct MainSettingsMenuViewController;
typedef struct __attribute__((__packed__)) MainSettingsMenuViewController {
	char _unused_data_useless[0x34];

	void* didSelectSettingsSubMenuEvent;
	struct MainSettingsTableView* _mainSettingsTableView;
	void* _settingsSubMenuInfos;
	void* _selectedSubMenuInfo;
	int _selectedSubMenuInfoIdx;
} MainSettingsMenuViewController_t;
struct MetronomeLevelStarter;
typedef struct __attribute__((__packed__)) MetronomeLevelStarter {
	char _unused_data_useless[0xC];

	struct BeatmapLevelSO* _level;
	struct BeatmapCharacteristicSO* _beatmapCharacteristic;
	enum BeatmapDifficulty _beatmapDifficulty;
	struct MenuTransitionsHelperSO* _menuTransitionsHelper;
	struct Button* _button;
	struct ButtonBinder* _buttonBinder;
} MetronomeLevelStarter_t;
struct MissionHelpViewController;
struct MissionHelpGameObjectPair;
typedef struct __attribute__((__packed__)) MissionHelpGameObjectPair {
	char _unused_data_useless[0x8];

	struct MissionHelpSO* missionHelp;
	void* gameObject;
} MissionHelpGameObjectPair_t;
typedef struct __attribute__((__packed__)) MissionHelpViewController {
	char _unused_data_useless[0x34];

	struct Button* _okButton;
	struct MissionHelpGameObjectPair* _missionHelpGameObjectPairs;
	void* didFinishEvent;
	struct MissionHelpSO* _missionHelp;
} MissionHelpViewController_t;
struct MissionLevelDetailViewController;
typedef struct __attribute__((__packed__)) MissionLevelDetailViewController {
	char _unused_data_useless[0x34];

	struct GameplayModifiersModelSO* _gameplayModifiersModel;
	struct Button* _playButton;
	struct TextMeshProUGUI* _songNameText;
	struct TextMeshProUGUI* _missionText;
	struct TextMeshProUGUI* _difficultyText;
	struct TextMeshProUGUI* _characteristicsText;
	void* _objectiveListItems;
	void* _gameplayModifierInfoListItemsList;
	void* _modifiersPanelGO;
	void* didPressPlayButtonEvent;
	struct MissionNode* _missionNode;
} MissionLevelDetailViewController_t;
struct MissionLevelModifiersViewController;
typedef struct __attribute__((__packed__)) MissionLevelModifiersViewController {
	char _unused_data_useless[0x34];

	struct GameplayModifiersModelSO* _gameplayModifiersModel;
	void* _gameplayModifierInfoListItemsList;
	void* _modifiersPanel;
	struct TextMeshProUGUI* _titleText;
	struct GameplayModifiers* _gameplayModifiers;
} MissionLevelModifiersViewController_t;
struct MissionResultsViewController;
struct MissionCompletionResults;
struct LevelCompletionResults;
struct BeatmapObjectExecutionRating;
enum BeatmapObjectExecutionRatingType {
	BeatmapObjectExecutionRatingType_Note,
	BeatmapObjectExecutionRatingType_Bomb,
	BeatmapObjectExecutionRatingType_Obstacle
};
typedef struct __attribute__((__packed__)) BeatmapObjectExecutionRating {
	char _unused_data_useless[0x8];

	enum BeatmapObjectExecutionRatingType beatmapObjectRatingType_k__BackingField;
	float time_k__BackingField;
} BeatmapObjectExecutionRating_t;
struct MultiplierValue;
typedef struct __attribute__((__packed__)) MultiplierValue {
	int multiplier_k__BackingField;
	float time_k__BackingField;
} MultiplierValue_t;
enum LevelEndStateType {
	LevelEndStateType_None,
	LevelEndStateType_Cleared,
	LevelEndStateType_Failed
};
enum LevelEndAction {
	LevelEndAction_None,
	LevelEndAction_Quit,
	LevelEndAction_Restart
};
typedef struct __attribute__((__packed__)) LevelCompletionResults {
	char _unused_data_useless[0x8];

	struct BeatmapObjectExecutionRating* beatmapObjectExecutionRatings_k__BackingField;
	struct MultiplierValue multiplierValues_k__BackingField;
	struct GameplayModifiers* gameplayModifiers_k__BackingField;
	struct GameplayModifiersModelSO* gameplayModifiersModel_k__BackingField;
	int modifiedScore_k__BackingField;
	int rawScore_k__BackingField;
	enum Rank rank_k__BackingField;
	char fullCombo_k__BackingField;
	void* saberActivityValues_k__BackingField;
	float leftSaberMovementDistance_k__BackingField;
	float rightSaberMovementDistance_k__BackingField;
	void* handActivityValues_k__BackingField;
	float leftHandMovementDistance_k__BackingField;
	float rightHandMovementDistance_k__BackingField;
	float songDuration_k__BackingField;
	enum LevelEndStateType levelEndStateType_k__BackingField;
	enum LevelEndAction levelEndAction_k__BackingField;
	float energy_k__BackingField;
	int goodCutsCount_k__BackingField;
	int badCutsCount_k__BackingField;
	int missedCount_k__BackingField;
	int notGoodCount_k__BackingField;
	int okCount_k__BackingField;
	int averageCutScore_k__BackingField;
	int maxCutScore_k__BackingField;
	int maxCombo_k__BackingField;
	float minDirDeviation_k__BackingField;
	float maxDirDeviation_k__BackingField;
	float averageDirDeviation_k__BackingField;
	float minTimeDeviation_k__BackingField;
	float maxTimeDeviation_k__BackingField;
	float averageTimeDeviation_k__BackingField;
	float endSongTime_k__BackingField;
} LevelCompletionResults_t;
struct MissionObjectiveResult;
typedef struct __attribute__((__packed__)) MissionObjectiveResult {
	char _unused_data_useless[0x8];

	struct MissionObjective* missionObjective_k__BackingField;
	char cleared_k__BackingField;
	int value_k__BackingField;
} MissionObjectiveResult_t;
typedef struct __attribute__((__packed__)) MissionCompletionResults {
	char _unused_data_useless[0x8];

	struct LevelCompletionResults* levelCompletionResults_k__BackingField;
	struct MissionObjectiveResult* missionObjectiveResults_k__BackingField;
} MissionCompletionResults_t;
typedef struct __attribute__((__packed__)) MissionResultsViewController {
	char _unused_data_useless[0x34];

	struct TextMeshProUGUI* _resultText;
	struct TextMeshProUGUI* _missionNameText;
	struct TextMeshProUGUI* _songNameText;
	void* _successIcon;
	void* _successIconGlow;
	struct Color _successColor;
	void* _failIcon;
	void* _failIconGlow;
	struct Color _failColor;
	void* _resultObjectiveListItemList;
	struct Button* _continueButton;
	struct Button* _retryButton;
	struct AudioClip* _levelClearedAudioClip;
	struct FireworksController* _fireworksController;
	struct SongPreviewPlayer* _songPreviewPlayer;
	void* continueButtonPressedEvent;
	void* retryButtonPressedEvent;
	struct MissionNode* _missionNode;
	struct MissionCompletionResults* _missionCompletionResults;
	void* _startFireworksAfterDelayCoroutine;
} MissionResultsViewController_t;
struct MissionSelectionMapViewController;
typedef struct __attribute__((__packed__)) MissionSelectionMapViewController {
	char _unused_data_useless[0x34];

	struct ScrollView* _mapScrollView;
	struct MissionNodeSelectionManager* _missionNodeSelectionManager;
	struct MissionMapAnimationController* _missionMapAnimationController;
	struct SongPreviewPlayer* _songPreviewPlayer;
	void* didSelectMissionLevelEvent;
	struct MissionNode* _selectedMissionNode;
} MissionSelectionMapViewController_t;
struct PlatformLeaderboardViewController;
typedef struct __attribute__((__packed__)) PlatformLeaderboardViewController {
	char _unused_data_useless[0x34];

	struct PlatformLeaderboardsModel* _leaderboardsModel;
	struct LeaderboardTableView* _leaderboardTableView;
	struct IconSegmentedControl* _scopeSegmentedControl;
	void* _loadingIndicator;
	struct TextMeshProUGUI* _infoText;
	void* _globalLeaderboardIcon;
	void* _aroundPlayerLeaderboardIcon;
	void* _friendsLeaderboardIcon;
	struct HMAsyncRequest* _getScoresAsyncRequest;
	void* _playerScorePos;
	void* _scores;
	void* _difficultyBeatmap;
	char _refreshIsNeeded;
	char _hasScoresData;
} PlatformLeaderboardViewController_t;
struct PlayerSelectionViewController;
typedef struct __attribute__((__packed__)) PlayerSelectionViewController {
	char _unused_data_useless[0x34];

	struct TextMeshProUGUI* _titleText;
	struct TextAndImageTableView* _playerSelectionTableView;
	void* _playerImage;
	struct Button* _cancelButton;
	struct Button* _addNewPlayerButton;
	void* didCancelEvent;
	void* didSelectPlayerEvent;
	void* requestsAddNewPlayerEvent;
	void* _players;
	struct PlayerDataModelSO* _playerDataModel;
} PlayerSelectionViewController_t;
struct PlayerStatisticsViewController;
struct StatsScopeData;
typedef struct __attribute__((__packed__)) StatsScopeData {
	cs_string* text_k__BackingField;
	void* playerOverallStatsDataFunc_k__BackingField;
} StatsScopeData_t;
typedef struct __attribute__((__packed__)) PlayerStatisticsViewController {
	char _unused_data_useless[0x34];

	struct PlayerDataModelSO* _playerDataModel;
	struct TextSegmentedControl* _statsScopeSegmentedControl;
	struct TextMeshProUGUI* _playedLevelsCountText;
	struct TextMeshProUGUI* _clearedLevelsCountText;
	struct TextMeshProUGUI* _failedLevelsCountText;
	struct TextMeshProUGUI* _timePlayedText;
	struct TextMeshProUGUI* _goodCutsCountText;
	struct TextMeshProUGUI* _badCutsCountCountText;
	struct TextMeshProUGUI* _missedCountText;
	struct TextMeshProUGUI* _averageCutScoreText;
	struct TextMeshProUGUI* _totalScoreText;
	struct TextMeshProUGUI* _fullComboCountText;
	struct TextMeshProUGUI* _handDistanceTravelledText;
	struct StatsScopeData _statsScopeDatas;
} PlayerStatisticsViewController_t;
struct PracticeViewController;
typedef struct __attribute__((__packed__)) PracticeViewController {
	char _unused_data_useless[0x34];

	void* _songStartScrollbar;
	void* _speedScrollbar;
	struct TextMeshProUGUI* _songNameText;
	struct Button* _backButton;
	struct Button* _playButton;
	struct SongPreviewPlayer* _songPreviewPlayer;
	void* didPressPlayButtonEvent;
	void* didFinishEvent;
	struct PracticeSettings* _practiceSettings;
	float _currentPlayingStartTime;
	float _maxStartSongTime;
	void* _level;
} PracticeViewController_t;
struct ReleaseInfoViewController;
typedef struct __attribute__((__packed__)) ReleaseInfoViewController {
	char _unused_data_useless[0x34];

	struct MainSettingsModel* _mainSettingsModel;
	struct TextPageScrollView* _textPageScrollView;
	void* _releaseNotesTextAsset;
	void* _firstTextAsset;
} ReleaseInfoViewController_t;
struct ResultsViewController;
typedef struct __attribute__((__packed__)) ResultsViewController {
	char _unused_data_useless[0x34];

	struct Button* _restartButton;
	struct Button* _continueButton;
	void* _failedPanel;
	void* _clearedPanel;
	struct TextMeshProUGUI* _scoreText;
	void* _newHighScoreText;
	struct TextMeshProUGUI* _rankText;
	struct TextMeshProUGUI* _goodCutsPercentageText;
	void* _fullComboText;
	struct TextMeshProUGUI* _clearedSongNameText;
	struct TextMeshProUGUI* _clearedDifficultyText;
	struct TextMeshProUGUI* _failedSongNameText;
	struct TextMeshProUGUI* _failedDifficultyText;
	struct AudioClip* _levelClearedAudioClip;
	struct FireworksController* _fireworksController;
	struct SongPreviewPlayer* _songPreviewPlayer;
	void* continueButtonPressedEvent;
	void* restartButtonPressedEvent;
	struct LevelCompletionResults* _levelCompletionResults;
	void* _difficultyBeatmap;
	void* _startFireworksAfterDelayCoroutine;
	char _newHighScore;
} ResultsViewController_t;
struct RoomAdjustSettingsViewController;
typedef struct __attribute__((__packed__)) RoomAdjustSettingsViewController {
	char _unused_data_useless[0x34];

	void* _roomCenter;
	void* _roomRotation;
	struct Button* _xIncButton;
	struct Button* _xDecButton;
	struct Button* _yIncButton;
	struct Button* _yDecButton;
	struct Button* _zIncButton;
	struct Button* _zDecButton;
	struct Button* _rotIncButton;
	struct Button* _rotDecButton;
	struct Button* _resetButton;
} RoomAdjustSettingsViewController_t;
struct SettingsNavigationController;
typedef struct __attribute__((__packed__)) SettingsNavigationController {
	char _unused_data_useless[0x3C];

	struct Button* _okButton;
	struct Button* _applyButton;
	struct Button* _cancelButton;
	void* didFinishEvent;
} SettingsNavigationController_t;
struct SimpleDialogPromptViewController;
typedef struct __attribute__((__packed__)) SimpleDialogPromptViewController {
	char _unused_data_useless[0x34];

	struct TextMeshProUGUI* _titleText;
	struct TextMeshProUGUI* _messageText;
	struct Button* _buttons;
	struct TextMeshProUGUI* _buttonTexts;
	void* _interactionBlocker;
	void* _didFinishAction;
} SimpleDialogPromptViewController_t;
struct SimpleRetailDemoViewController;
typedef struct __attribute__((__packed__)) SimpleRetailDemoViewController {
	char _unused_data_useless[0x34];

	struct Button* _tutorialButton;
	struct Button* _playLevel1Button;
	struct Button* _playLevel2Button;
	struct Button* _exitButton;
	void* didFinishEvent;
} SimpleRetailDemoViewController_t;
struct SoloModeSelectionViewController;
typedef struct __attribute__((__packed__)) SoloModeSelectionViewController {
	char _unused_data_useless[0x34];

	struct Button* _freePlayModeButton;
	struct Button* _oneSaberModeButton;
	struct Button* _noArrowsModeButton;
	struct Button* _dismissButton;
	void* didFinishEvent;
} SoloModeSelectionViewController_t;
struct StandardLevelDetailViewController;
typedef struct __attribute__((__packed__)) StandardLevelDetailViewController {
	char _unused_data_useless[0x34];

	struct StandardLevelDetailView* _standardLevelDetailView;
	struct StandardLevelBuyView* _standardLevelBuyView;
	struct StandardLevelBuyInfoView* _standardLevelBuyInfoView;
	struct LoadingControl* _loadingControl;
	struct AdditionalContentModelSO* _additionalContentModel;
	struct BeatmapLevelsModelSO* _beatmapLevelsModel;
	struct PlayerDataModelSO* _playerDataModel;
	void* didPressPlayButtonEvent;
	void* didPressPracticeButtonEvent;
	void* didChangeDifficultyBeatmapEvent;
	void* didPresentContentEvent;
	struct EventBinder* _eventBinder;
	void* _cancellationTokenSource;
	void* _previewLevel;
	void* _beatmapLevel;
	void* _pack;
	void* _player;
	char _showPlayerStats;
	void* _loadingLevelCancellationTokenSource;
} StandardLevelDetailViewController_t;
struct DemoMenuLevelPanelView;
typedef struct __attribute__((__packed__)) DemoMenuLevelPanelView {
	char _unused_data_useless[0xC];

	struct LocalLeaderboardsModel* _localLeaderboardsModel;
	struct Button* _playButton;
	struct TextMeshProUGUI* _songNameText;
	struct TextMeshProUGUI* _difficultyText;
	void* _localLeaderboardTableView;
	void* playButtonWasPressedEvent;
	struct ButtonBinder* _buttonBinder;
} DemoMenuLevelPanelView_t;
struct DifficultyTableView;
typedef struct __attribute__((__packed__)) DifficultyTableView {
	char _unused_data_useless[0xC];

	struct TableView* _tableView;
	struct DifficultyTableCell* _cellPrefab;
	struct DifficultyTableCell* _nonSelectableCellPrefab;
	float _cellHeight;
	void* didSelectRow;
	void* _difficultyBeatmaps;
} DifficultyTableView_t;
struct LeaderboardTableView;
typedef struct __attribute__((__packed__)) LeaderboardTableView {
	char _unused_data_useless[0xC];

	struct TableView* _tableView;
	struct LeaderboardTableCell* _cellPrefab;
	float _rowHeight;
	void* _scores;
	int _specialScorePos;
} LeaderboardTableView_t;
struct LevelPackLevelsTableView;
typedef struct __attribute__((__packed__)) LevelPackLevelsTableView {
	char _unused_data_useless[0xC];

	struct TableView* _tableView;
	struct LevelListTableCell* _levelCellPrefab;
	cs_string* _levelCellsReuseIdentifier;
	struct LevelPackHeaderTableCell* _packCellPrefab;
	cs_string* _packCellsReuseIdentifier;
	float _cellHeight;
	struct AdditionalContentModelSO* _additionalContentModel;
	void* didSelectLevelEvent;
	void* didSelectPackEvent;
	void* _pack;
	char _isInitialized;
	int _selectedRow;
	char _showLevelPackHeader;
} LevelPackLevelsTableView_t;
struct LevelPacksTableView;
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
struct MainSettingsTableView;
typedef struct __attribute__((__packed__)) MainSettingsTableView {
	char _unused_data_useless[0xC];

	struct TableView* _tableView;
	struct MainSettingsTableCell* _cellPrefab;
	float _cellHeight;
	void* didSelectRowEvent;
	void* _settingsSubMenuInfos;
} MainSettingsTableView_t;
struct ScrollView;
typedef struct __attribute__((__packed__)) ScrollView {
	char _unused_data_useless[0xC];

	void* _viewport;
	void* _contentRectTransform;
	struct Button* _pageUpButton;
	struct Button* _pageDownButton;
	struct VerticalScrollIndicator* _verticalScrollIndicator;
	float _smooth;
	float _pageStepRelativePosition;
	float _scrollItemRelativeThresholdPosition;
	struct ButtonBinder* _buttonBinder;
	float _dstPosY;
	float _scrollPageHeight;
	float _contentHeight;
	void* _scrollFocusPosYs;
} ScrollView_t;
struct StandardLevelBuyInfoView;
typedef struct __attribute__((__packed__)) StandardLevelBuyInfoView {
	char _unused_data_useless[0xC];

	struct TextMeshProUGUI* _text;
	struct Button* _buyLevelButton;
	struct Button* _buyPackButton;
} StandardLevelBuyInfoView_t;
struct StandardLevelBuyView;
typedef struct __attribute__((__packed__)) StandardLevelBuyView {
	char _unused_data_useless[0xC];

	struct TextMeshProUGUI* _songNameText;
	struct BasicLevelParamsPanel* _levelParamsPanel;
	struct RawImage* _coverRawImage;
	struct Button* _buyButton;
	cs_string* _SettingTextureLevelId;
	void* _cancellationTokenSource;
} StandardLevelBuyView_t;
struct StandardLevelDetailView;
typedef struct __attribute__((__packed__)) StandardLevelDetailView {
	char _unused_data_useless[0xC];

	struct Button* _playButton;
	struct Button* _practiceButton;
	struct TextMeshProUGUI* _songNameText;
	struct LevelParamsPanel* _levelParamsPanel;
	struct TextMeshProUGUI* _highScoreText;
	struct TextMeshProUGUI* _maxComboText;
	struct TextMeshProUGUI* _maxRankText;
	struct RawImage* _coverImage;
	struct BeatmapDifficultySegmentedControlController* _beatmapDifficultySegmentedControlController;
	struct BeatmapCharacteristicSegmentedControlController* _beatmapCharacteristicSegmentedControlController;
	void* _playerStatsContainer;
	void* didChangeDifficultyBeatmapEvent;
	char _showPlayerStats;
	void* _level;
	void* _player;
	void* _selectedDifficultyBeatmap;
	cs_string* _settingTextureForLevelId;
	void* _cancellationTokenSource;
} StandardLevelDetailView_t;
struct TextAndImageTableView;
struct Item;
typedef struct __attribute__((__packed__)) Item {
	char _unused_data_useless[0x8];

	cs_string* text;
	void* image;
} Item_t;
typedef struct __attribute__((__packed__)) TextAndImageTableView {
	char _unused_data_useless[0xC];

	struct TableView* _tableView;
	struct TextAndImageTableCell* _cellPrefab;
	float _cellWidth;
	void* didSelectColumnEvent;
	struct Item* _items;
} TextAndImageTableView_t;
struct TextPageScrollView;
typedef struct __attribute__((__packed__)) TextPageScrollView {
	char _unused_data_useless[0xC];

	void* _viewport;
	struct TextMeshProUGUI* _text;
	struct Button* _pageUpButton;
	struct Button* _pageDownButton;
	struct VerticalScrollIndicator* _verticalScrollIndicator;
	float _smooth;
	void* _contentRectTransform;
	struct ButtonBinder* _buttonBinder;
	float _dstPosY;
	float _scrollPageHeight;
	float _contentHeight;
} TextPageScrollView_t;
struct XWeaponTrail;
struct ElementPool;
typedef struct __attribute__((__packed__)) ElementPool {
	char _unused_data_useless[0x8];

	void* _stack;
	int CountAll_k__BackingField;
} ElementPool_t;
struct Spline;
typedef struct __attribute__((__packed__)) Spline {
	char _unused_data_useless[0x8];

	void* mControlPoints;
	void* mSegments;
} Spline_t;
struct VertexPool;
typedef struct __attribute__((__packed__)) VertexPool {
	char _unused_data_useless[0x8];

	struct Vector3 vertices;
	void* indices;
	struct Vector2 uvs;
	struct Color colors;
	char indiceChanged;
	char colorChanged;
	char uvChanged;
	char vertChanged;
	char uv2Changed;
	int _vertexTotal;
	int _vertexUsed;
	int _indexTotal;
	int _indexUsed;
	char _vertCountChanged;
	void* _mesh;
} VertexPool_t;
struct VertexSegment;
typedef struct __attribute__((__packed__)) VertexSegment {
	char _unused_data_useless[0x8];

	int VertStart;
	int IndexStart;
	int VertCount;
	int IndexCount;
	struct VertexPool* Pool;
} VertexSegment_t;
typedef struct __attribute__((__packed__)) XWeaponTrail {
	char _unused_data_useless[0xC];

	struct XWeaponTrailRenderer* _trailRendererPrefab;
	void* _pointStart;
	void* _pointEnd;
	int _maxFrame;
	int _granularity;
	struct Color _color;
	int _skipFirstFrames;
	float _trailWidth;
	void* _snapshotList;
	struct ElementPool* _elemPool;
	struct Spline* _spline;
	struct VertexPool* _vertexPool;
	struct VertexSegment* _vertexSegment;
	struct XWeaponTrailRenderer* _trailRenderer;
	int _frameNum;
} XWeaponTrail_t;
struct PlatformSettings;
typedef struct __attribute__((__packed__)) PlatformSettings {
	char _unused_data_useless[0xC];

	cs_string* ovrAppID;
	cs_string* ovrMobileAppID;
	char ovrUseStandalonePlatform;
	char ovrEnableARM64Support;
} PlatformSettings_t;
struct VRGraphicRaycaster;
typedef struct __attribute__((__packed__)) VRGraphicRaycaster {
	char _unused_data_useless[0xC];

	struct LayerMask _blockingMask;
	void* _mainCamera;
	void* _canvas;
	void* _eventCamera;
	void* m_RaycastResults;
} VRGraphicRaycaster_t;
struct VRInputModule;
struct MouseState;
typedef struct __attribute__((__packed__)) MouseState {
	char _unused_data_useless[0x8];

	void* _trackedButtons;
} MouseState_t;
typedef struct __attribute__((__packed__)) VRInputModule {
	char _unused_data_useless[0x24];

	struct VRPointer* _vrPointer;
	char useMouseForPressInput_k__BackingField;
	void* _pointerData;
	void* _componentList;
	struct MouseState* _mouseState;
} VRInputModule_t;
struct VRPointer;
typedef struct __attribute__((__packed__)) VRPointer {
	char _unused_data_useless[0xC];

	struct VRController* _leftVRController;
	struct VRController* _rightVRController;
	void* _laserPointerPrefab;
	void* _cursorPrefab;
	float _defaultLaserPointerLength;
	float _laserPointerWidth;
	void* _laserPointerTransform;
	void* _cursorTransform;
	void* _eventSystem;
	struct VRController* _vrController;
	void* _pointerData;
} VRPointer_t;
struct VRUIHierarchyManager;
typedef struct __attribute__((__packed__)) VRUIHierarchyManager {
	char _unused_data_useless[0xC];

	void* _screenSystem;
	struct FlowCoordinator* _rootFlowCoordinator;
} VRUIHierarchyManager_t;
struct VRUINavigationController;
typedef struct __attribute__((__packed__)) VRUINavigationController {
	char _unused_data_useless[0x33];

	char _fullscreenMode;
	void* _controllersContainer;
	void* _viewControllers;
} VRUINavigationController_t;
struct VRUITitleBar;
typedef struct __attribute__((__packed__)) VRUITitleBar {
	char _unused_data_useless[0xC];

	struct TextMeshProUGUI* _textMesh;
	float _defaultYScale;
	cs_string* _text;
	float _destAnimationValue;
} VRUITitleBar_t;
struct ButtonStaticAnimations;
typedef struct __attribute__((__packed__)) ButtonStaticAnimations {
	char _unused_data_useless[0xC];

	struct NoTransitionsButton* _button;
	void* _normalClip;
	void* _highlightedClip;
	void* _pressedClip;
	void* _disabledClip;
	char _didStart;
} ButtonStaticAnimations_t;
struct IconSegmentedControl;
struct DiContainer;
struct LazyInstanceInjector;
typedef struct __attribute__((__packed__)) LazyInstanceInjector {
	char _unused_data_useless[0x8];

	struct DiContainer* _container;
	void* _instancesToInject;
} LazyInstanceInjector_t;
struct SingletonMarkRegistry;
typedef struct __attribute__((__packed__)) SingletonMarkRegistry {
	char _unused_data_useless[0x8];

	void* _boundSingletons;
	void* _boundNonSingletons;
} SingletonMarkRegistry_t;
typedef struct __attribute__((__packed__)) DiContainer {
	char _unused_data_useless[0x8];

	void* _decorators;
	void* _providers;
	struct DiContainer* _containerLookups;
	void* _resolvesInProgress;
	void* _resolvesTwiceInProgress;
	struct LazyInstanceInjector* _lazyInjector;
	struct SingletonMarkRegistry* _singletonMarkRegistry;
	void* _currentBindings;
	void* _childBindings;
	void* _validatedTypes;
	void* _validationQueue;
	void* _contextTransform;
	char _hasLookedUpContextTransform;
	void* _inheritedDefaultParent;
	void* _explicitDefaultParent;
	char _hasExplicitDefaultParent;
	void* _settings;
	char _hasResolvedRoots;
	char _isFinalizingBinding;
	char _isValidating;
	char _isInstalling;
	char AssertOnNewGameObjects_k__BackingField;
} DiContainer_t;
struct DataItem;
typedef struct __attribute__((__packed__)) DataItem {
	char _unused_data_useless[0x8];

	void* icon_k__BackingField;
	cs_string* hintText_k__BackingField;
} DataItem_t;
typedef struct __attribute__((__packed__)) IconSegmentedControl {
	char _unused_data_useless[0x28];

	struct IconSegmentedControlCell* _firstCellPrefab;
	struct IconSegmentedControlCell* _lastCellPrefab;
	struct IconSegmentedControlCell* _middleCellPrefab;
	struct IconSegmentedControlCell* _singleCellPrefab;
	struct DiContainer* _container;
	struct DataItem* _dataItems;
	char _isInitialized;
} IconSegmentedControl_t;
struct IconSegmentedControlCell;
typedef struct __attribute__((__packed__)) IconSegmentedControlCell {
	char _unused_data_useless[0x1C];

	struct Image* _icon;
	struct Image* _bgImage;
	struct HoverHint* _hoverHint;
	struct Color _normalIconColor;
	struct Color _selectedIconColor;
	struct Color _highlightIconColor;
	struct Color _selectedHighlightIconColor;
	struct Color _normalBGColor;
	struct Color _selectedBGColor;
	struct Color _highlightBGColor;
	struct Color _selectedHighlightBGColor;
} IconSegmentedControlCell_t;
struct Image;
enum Type {
	Type_Simple,
	Type_Sliced,
	Type_Tiled,
	Type_Filled
};
enum FillMethod {
	FillMethod_Horizontal,
	FillMethod_Vertical,
	FillMethod_Radial90,
	FillMethod_Radial180,
	FillMethod_Radial360
};
typedef struct __attribute__((__packed__)) Image {
	char _unused_data_useless[0x64];

	void* m_Sprite;
	void* m_OverrideSprite;
	enum Type m_Type;
	char m_PreserveAspect;
	char m_FillCenter;
	enum FillMethod m_FillMethod;
	float m_FillAmount;
	char m_FillClockwise;
	int m_FillOrigin;
	float m_EventAlphaThreshold;
} Image_t;
struct Scrollbar;
typedef struct __attribute__((__packed__)) Scrollbar {
	char _unused_data_useless[0x94];

	struct TextMeshProUGUI* m_ValueText;
	void* m_HandleRect;
	enum Direction m_Direction;
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
struct SectionTableView;
struct Section;
typedef struct __attribute__((__packed__)) Section {
	char unfolded;
	int startBaseRow;
	int numberOfBaseRows;
} Section_t;
typedef struct __attribute__((__packed__)) SectionTableView {
	char _unused_data_useless[0x68];

	char _unfoldSectionsByDefault;
	void* didSelectRowInSectionEvent;
	void* didSelectHeaderEvent;
	void* _dataSource;
	struct Section _sections;
} SectionTableView_t;
struct SegmentedControl;
typedef struct __attribute__((__packed__)) SegmentedControl {
	char _unused_data_useless[0xC];

	void* _separatorPrefab;
	void* didSelectCellEvent;
	int _numberOfCells;
	void* _cells;
	void* _separators;
	void* _dataSource;
	int _selectedCellNumber;
} SegmentedControl_t;
struct SegmentedControlCell;
typedef struct __attribute__((__packed__)) SegmentedControlCell {
	char _unused_data_useless[0xC];

	struct Signal* _segmentedControlCellWasPressedSignal;
	int _cellNumber;
	struct SegmentedControl* _segmentedControl;
	char _selected;
	char _highlighted;
} SegmentedControlCell_t;
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
struct TableView;
enum TableType {
	TableType_Vertical,
	TableType_Horizontal
};
enum TableViewSelectionType {
	TableViewSelectionType_None,
	TableViewSelectionType_Single,
	TableViewSelectionType_Multiple
};
struct CellsGroup;
typedef struct __attribute__((__packed__)) CellsGroup {
	char _unused_data_useless[0x8];

	cs_string* reuseIdentifier;
	void* cells;
} CellsGroup_t;
struct ScrollRect;
enum MovementType {
	MovementType_Unrestricted,
	MovementType_Elastic,
	MovementType_Clamped
};
enum ScrollbarVisibility {
	ScrollbarVisibility_Permanent,
	ScrollbarVisibility_AutoHide,
	ScrollbarVisibility_AutoHideAndExpandViewport
};
typedef struct __attribute__((__packed__)) ScrollRect {
	char _unused_data_useless[0xC];

	void* m_Content;
	char m_Horizontal;
	char m_Vertical;
	enum MovementType m_MovementType;
	float m_Elasticity;
	char m_Inertia;
	float m_DecelerationRate;
	float m_ScrollSensitivity;
	void* m_Viewport;
	struct Scrollbar* m_HorizontalScrollbar;
	struct Scrollbar* m_VerticalScrollbar;
	enum ScrollbarVisibility m_HorizontalScrollbarVisibility;
	enum ScrollbarVisibility m_VerticalScrollbarVisibility;
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
typedef struct __attribute__((__packed__)) TableView {
	char _unused_data_useless[0xC];

	char _hideScrollButtonsIfNotNeeded;
	struct Button* _pageUpButton;
	struct Button* _pageDownButton;
	char _alignToCenter;
	enum TableType _tableType;
	enum TableViewSelectionType _selectionType;
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
struct TextScrollbar;
typedef struct __attribute__((__packed__)) TextScrollbar {
	char _unused_data_useless[0xC];

	struct TextMeshProUGUI* _text;
	struct Scrollbar* _scrollbar;
	float _minValue;
	float _maxValue;
	int _numberOfSteps;
	void* onValueChangedEvent;
} TextScrollbar_t;
struct TextSegmentedControl;
typedef struct __attribute__((__packed__)) TextSegmentedControl {
	char _unused_data_useless[0x28];

	float _fontSize;
	float _padding;
	void* _firstCellPrefab;
	void* _lastCellPrefab;
	void* _singleCellPrefab;
	void* _middleCellPrefab;
	struct DiContainer* _container;
	void* _texts;
} TextSegmentedControl_t;
struct TextSegmentedControlCell;
typedef struct __attribute__((__packed__)) TextSegmentedControlCell {
	char _unused_data_useless[0x20];

	struct Image* _bgImage;
	struct Image* _highlightImage;
} TextSegmentedControlCell_t;
struct TextSegmentedControlCellNew;
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
struct VerticalScrollIndicator;
typedef struct __attribute__((__packed__)) VerticalScrollIndicator {
	char _unused_data_useless[0xC];

	void* _handle;
	float _progress;
	float _normalizedPageHeight;
} VerticalScrollIndicator_t;
enum ActivationType {
	ActivationType_AddedToHierarchy,
	ActivationType_NotAddedToHierarchy
};
enum DeactivationType {
	DeactivationType_RemovedFromHierarchy,
	DeactivationType_NotRemovedFromHierarchy
};
struct NamedPreset;
typedef struct __attribute__((__packed__)) NamedPreset {
	char _unused_data_useless[0x8];

	cs_string* presetName;
} NamedPreset_t;
enum WeightsType {
	WeightsType_None,
	WeightsType_AlphaWeights,
	WeightsType_AlphaAndDepthWeights
};
struct DifficultyBeatmapWithLevelCompletionResults;
typedef struct __attribute__((__packed__)) DifficultyBeatmapWithLevelCompletionResults {
	void* _difficultyBeatmap;
	struct LevelCompletionResults* _levelCompletionResults;
} DifficultyBeatmapWithLevelCompletionResults_t;
enum LeaderboardType {
	LeaderboardType_AllTime,
	LeaderboardType_Daily
};
struct LeaderboardData;
typedef struct __attribute__((__packed__)) LeaderboardData {
	char _unused_data_useless[0x8];

	cs_string* _leaderboardId;
	void* _scores;
} LeaderboardData_t;
enum ScoresScope {
	ScoresScope_Global,
	ScoresScope_AroundPlayer,
	ScoresScope_Friends
};
struct LevelDataAssetDownloadUpdate;
enum AssetDownloadingState {
	AssetDownloadingState_PreparingToDownload,
	AssetDownloadingState_Downloading,
	AssetDownloadingState_Completed
};
typedef struct __attribute__((__packed__)) LevelDataAssetDownloadUpdate {
	cs_string* levelID;
	unsigned int bytesTotal;
	unsigned int bytesTransferred;
	enum AssetDownloadingState assetDownloadingState;
} LevelDataAssetDownloadUpdate_t;
struct PlayerDataModelSaveData;
typedef struct __attribute__((__packed__)) PlayerDataModelSaveData {
	char _unused_data_useless[0x8];

	cs_string* version;
	void* localPlayers;
	void* guestPlayers;
	enum BeatmapDifficulty lastSelectedBeatmapDifficulty;
} PlayerDataModelSaveData_t;
struct PlayerDataModelSaveDataV1_0_1;
typedef struct __attribute__((__packed__)) PlayerDataModelSaveDataV1_0_1 {
	char _unused_data_useless[0x8];

	cs_string* version;
	void* localPlayers;
	void* guestPlayers;
	enum BeatmapDifficulty lastSelectedBeatmapDifficulty;
} PlayerDataModelSaveDataV1_0_1_t;
enum TutorialEndStateType {
	TutorialEndStateType_Completed,
	TutorialEndStateType_ReturnToMenu,
	TutorialEndStateType_Restart
};
struct RingRotationEffect;
typedef struct __attribute__((__packed__)) RingRotationEffect {
	char _unused_data_useless[0x8];

	float _progressPos;
	float _rotationAngle;
	float _rotationStep;
	float _rotationPropagationSpeed;
	float _rotationFlexySpeed;
} RingRotationEffect_t;
struct AfterCutScoreHandler;
struct NoteExecutionRating;
enum Rating {
	Rating_GoodCut,
	Rating_Missed,
	Rating_BadCut
};
typedef struct __attribute__((__packed__)) NoteExecutionRating {
	char _unused_data_useless[0x10];

	enum Rating rating_k__BackingField;
	int cutScore_k__BackingField;
	float cutTimeDeviation_k__BackingField;
	float cutDirDeviation_k__BackingField;
} NoteExecutionRating_t;
typedef struct __attribute__((__packed__)) AfterCutScoreHandler {
	char _unused_data_useless[0x8];

	void* _finishCallback;
	struct NoteExecutionRating* _noteExecutionRating;
	struct NoteCutInfo* _noteCutInfo;
} AfterCutScoreHandler_t;
struct AfterCutScoreBuffer;
typedef struct __attribute__((__packed__)) AfterCutScoreBuffer {
	char _unused_data_useless[0x10];

	void* didFinishEvent;
	int _afterCutScoreWithMultiplier;
	int _beforeCutScoreWithMultiplier;
	int _multiplier;
	struct NoteCutInfo* _noteCutInfo;
} AfterCutScoreBuffer_t;
struct Element;
typedef struct __attribute__((__packed__)) Element {
	char _unused_data_useless[0x8];

	int idx;
	float velocity;
} Element_t;
struct TutorialObstacleSpawnData;
typedef struct __attribute__((__packed__)) TutorialObstacleSpawnData {
	char _unused_data_useless[0x14];

	int lineIndex;
	int width;
	enum ObstacleType obstacleType;
} TutorialObstacleSpawnData_t;
struct TutorialNoteSpawnData;
typedef struct __attribute__((__packed__)) TutorialNoteSpawnData {
	char _unused_data_useless[0x14];

	int lineIndex;
	enum NoteLineLayer noteLineLayer;
	enum NoteCutDirection cutDirection;
	enum NoteType noteType;
} TutorialNoteSpawnData_t;
enum TransitionType {
	TransitionType_Instant,
	TransitionType_Animated
};
enum ContentType {
	ContentType_Loading,
	ContentType_OwnedAndReady,
	ContentType_OwnedAndDownloading,
	ContentType_Buy,
	ContentType_BuyInfo,
	ContentType_Error
};
enum MenuButton {
	MenuButton_SoloFreePlay,
	MenuButton_Party,
	MenuButton_Multiplayer,
	MenuButton_BeatmapEditor,
	MenuButton_SoloCampaign,
	MenuButton_Settings,
	MenuButton_PlayerSettings,
	MenuButton_FloorAdjust,
	MenuButton_HowToPlay,
	MenuButton_Credits,
	MenuButton_Quit
};
enum FinishAction {
	FinishAction_Cancel,
	FinishAction_Ok,
	FinishAction_Apply
};
enum GetScoresResult {
	GetScoresResult_OK,
	GetScoresResult_Failed
};
struct LeaderboardScore;
typedef struct __attribute__((__packed__)) LeaderboardScore {
	char _unused_data_useless[0x8];

	int score_k__BackingField;
	int rank_k__BackingField;
	cs_string* playerName_k__BackingField;
	cs_string* playerId_k__BackingField;
	void* gameplayModifiers_k__BackingField;
} LeaderboardScore_t;
enum MenuType {
	MenuType_FreePlayMode,
	MenuType_NoArrowsMode,
	MenuType_OneSaberMode,
	MenuType_Back
};
struct LevelDownloadingUpdate;
enum DownloadingState {
	DownloadingState_PreparingToDownload,
	DownloadingState_Downloading,
	DownloadingState_Completed
};
typedef struct __attribute__((__packed__)) LevelDownloadingUpdate {
	cs_string* levelID;
	unsigned int bytesTotal;
	unsigned int bytesTransferred;
	enum DownloadingState downloadingState;
} LevelDownloadingUpdate_t;
struct Ray;
typedef struct __attribute__((__packed__)) Ray {
	struct Vector3 m_Origin;
	struct Vector3 m_Direction;
} Ray_t;
struct MouseButtonEventData;
typedef struct __attribute__((__packed__)) MouseButtonEventData {
	char _unused_data_useless[0x8];

	void* buttonState;
	void* buttonData;
} MouseButtonEventData_t;
struct VertexHelper;
typedef struct __attribute__((__packed__)) VertexHelper {
	char _unused_data_useless[0x8];

	void* m_Positions;
	void* m_Colors;
	void* m_Uv0S;
	void* m_Uv1S;
	void* m_Uv2S;
	void* m_Uv3S;
	void* m_Normals;
	void* m_Tangents;
	void* m_Indices;
	char m_ListsInitalized;
} VertexHelper_t;
enum CanvasUpdate {
	CanvasUpdate_Prelayout,
	CanvasUpdate_Layout,
	CanvasUpdate_PostLayout,
	CanvasUpdate_PreRender,
	CanvasUpdate_LatePreRender,
	CanvasUpdate_MaxUpdateValue
};
enum Axis {
	Axis_Horizontal,
	Axis_Vertical
};
struct Selectable;
struct Navigation;
typedef struct __attribute__((__packed__)) Navigation {
	enum Mode m_Mode;
	struct Selectable* m_SelectOnUp;
	struct Selectable* m_SelectOnDown;
	struct Selectable* m_SelectOnLeft;
	struct Selectable* m_SelectOnRight;
} Navigation_t;
enum Transition {
	Transition_None,
	Transition_ColorTint,
	Transition_SpriteSwap,
	Transition_Animation
};
struct ColorBlock;
typedef struct __attribute__((__packed__)) ColorBlock {
	struct Color m_NormalColor;
	struct Color m_HighlightedColor;
	struct Color m_PressedColor;
	struct Color m_DisabledColor;
	float m_ColorMultiplier;
	float m_FadeDuration;
} ColorBlock_t;
struct SpriteState;
typedef struct __attribute__((__packed__)) SpriteState {
	void* m_HighlightedSprite;
	void* m_PressedSprite;
	void* m_DisabledSprite;
} SpriteState_t;
struct AnimationTriggers;
typedef struct __attribute__((__packed__)) AnimationTriggers {
	char _unused_data_useless[0x8];

	cs_string* m_NormalTrigger;
	cs_string* m_HighlightedTrigger;
	cs_string* m_PressedTrigger;
	cs_string* m_DisabledTrigger;
} AnimationTriggers_t;
struct Graphic;
typedef struct __attribute__((__packed__)) Graphic {
	char _unused_data_useless[0xC];

	void* m_Material;
	struct Color m_Color;
	char m_RaycastTarget;
	void* m_RectTransform;
	struct CanvasRenderer* m_CanvasRenderer;
	void* m_Canvas;
	char m_VertsDirty;
	char m_MaterialDirty;
	void* m_OnDirtyLayoutCallback;
	void* m_OnDirtyVertsCallback;
	void* m_OnDirtyMaterialCallback;
	void* m_ColorTweenRunner;
	char useLegacyMeshGeneration_k__BackingField;
} Graphic_t;
typedef struct __attribute__((__packed__)) Selectable {
	char _unused_data_useless[0xC];

	struct Navigation m_Navigation;
	enum Transition m_Transition;
	struct ColorBlock m_Colors;
	struct SpriteState m_SpriteState;
	struct AnimationTriggers* m_AnimationTriggers;
	char m_Interactable;
	struct Graphic* m_TargetGraphic;
	char m_GroupsAllowInteraction;
	enum SelectionState m_CurrentSelectionState;
	char isPointerInside_k__BackingField;
	char isPointerDown_k__BackingField;
	char hasSelection_k__BackingField;
	void* m_CanvasGroupCache;
} Selectable_t;
enum ScrollPositionType {
	ScrollPositionType_Beginning,
	ScrollPositionType_Center,
	ScrollPositionType_End
};
