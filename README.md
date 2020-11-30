# Quest Hitscore Visualizer

This is an Oculus Quest standalone port of the original Hit Score Visualizer on PC.

## Installation

Download from the releases page (or the latest build artifact) and install it to BMBF.

## Configuration Types

This section describes the non-trivial types used in HSV's configuration.

These types were created for HSV configuration `v2.4.4`.

### Judgment Type

Each judgment has the following properties:

- `threshold`:
  - Type: `int`
  - Default: `0`
  - Threshold that the score must be greater than or equal to display this judgment.
- `text`:
  - Type: `string`
  - Required if `displayMode` is not `numeric` or `imageOnly`
  - The text to display with the judgment. Can provide format specifiers (described below) if the `displayMode` is `format` or better.
- `color`:
  - Type: `float[4]`
  - Default: `[0, 0, 0, 0]`
  - The color to display with the judgment. Must be of length 4.
- `fade`:
  - Type: `bool`
  - Default: `false`
  - Whether to fade the color between the last matching judgment and this one.
- `imagePath`:
  - Type: `string`
  - Path to an image of any Unity supported format. This is only used when `displayMode` is either `imageOnly` or `textAndImage`.
  - If this is not provided with `displayMode` `textAndImage`, it will fallback to only using the `text`.
- `soundPath`:
  - Type: `string`
  - Path to a `.wav`, `.mp3`, or `.ogg` audio file to play for this judgment.
- `soundVolume`:
  - Type: `float`
  - The volume to play the `soundPath` at.

### Judgment Format Text

This section outlines available format specifiers for judgment text.

- `%n`: A `\n` character, a newline.
- `%%`: A `%` character.
- `%b`: The before cut score value (from 0-70).
- `%c`: The cut distance score value (from 0-15).
- `%a`: The after cut score value (from 0-30).
- `%B`: Use the matching before cut segment's text.
- `%C`: Use the matching cut distance segment's text.
- `%A`: Use the matching after cut segment's text.
- `%s`: The score value (0-115).
- `%p`: The percentage of your score (0.00-100.00).
- `%` followed by any other character: Unchanged.

### Segment Type

- `threshold`:
  - Type: `int`
  - Default: `0`
  - Threshold that the segment score must be greater than or equal to display this segment.
- `text`:
  - Type: `string`
  - Text to display for this segment (used as `%B`, `%C`, or `%A` in `judgment`, with a format text option).
- `imagePath`:
  - Type: `string`
  - Path to an image of any Unity supported format. This is only used when `displayMode` is either `imageOnly` or `textAndImage`.

## Configuration Properties

HSV is configurable (almost _too_ configurable) and this section details its many configuration options.

Each of the following headers is a top-level configuration property, which may or may not be required. Properties provided but are otherwise not valid (including additional properties) will be ignored and the config file will be updated to remove them.

Configuration properties that are required but not provided will result in HSV not performing any changes to scores.

These properties match HSV configuration `v2.4.4`.

If a configuration is provided that is <= `v2.4.0`, it will automatically be set to default (the default of all properties in this specification, for `v2.4.4`).

### majorVersion

Type: `int`
Default: `2`
Required.

Indicates the major version of the configuration.

### minorVersion

Type: `int`
Default: `4`
Required.

Indicates the minor version of the configuration.

### patchVersion

Type: `int`
Default: `4`
Required.

Indicates the patch version of the configuration.

### isDefaultConfig

Type: `bool`
Default: `true`

Indicates whether the configuration should be replaced on updates to the mod/configuration version. This should be set to `false` when making custom configurations.

### displayMode

Type: `string`
Default: `format`
Required.

Must be one of the following:

- `format`: Formats text to display for each score. Allows for format specifiers. See `judgments` for a list of available format specifiers.
- `numeric`: Only show the score
- `textOnly`: Only show text
- `scoreOnTop`: Score above the text
- `textOnTop`: Text above the score
- `imageOnly`: If an image exists, will only display an image. Otherwise, it will fallback to `format`.
- `imageAndText`: If an image exists, will display the image in conjunction with the text. Otherwise, it will fallback to `format`.
- Otherwise, will fallback to: `textOnTop`

### useFixedPos

Type: `bool`
Default: `false`

Whether to force the visualization to always appear in a single, fixed location.

### fixedPosX

Type: `float`
Default: `0`

The x position to force the visualization to appear at. Only used if `useFixedPos` is `true`.

### fixedPosY

Type: `float`
Default: `0`

The y position to force the visualization to appear at. Only used if `useFixedPos` is `true`.

### fixedPosZ

Type: `float`
Default: `0`

The z position to force the visualization to appear at. Only used if `useFixedPos` is `true`.

### type

Type: `int`
Default: `0`

The available options are:

- `0`: Standard Configuration
- `1`: Christmas
- `2`: Easter

### useSeasonalThemes

Type: `bool`
Default: `true`

Whether to use seasonal themes and to convert between them.

### backupBeforeSeason

Type: `bool`
Default: `true`

Whether to back up the configuration before overriting it on a seasonal change. This is only used if `useSeasonalThemes` is `true`.

### restoreAfterSeason

Type: `bool`
Default: `true`

Whether to restore the confifugration after a seasonal change.

### doIntermediateUpdates

Type: `bool`
Default: `true`

Whether to perform intermediate updates on the score as it is processing.

### showInitialScore

Type: `bool`
Default: `false`

Whether to show an un-processed version of the score before it gets updated or displayed by HSV.

### judgments

Type: `judgment[]`
Default: Several default judgment objects
Required.

`judgments` is an array of `judgment` objects arranged in descending order of `threshold`.

### beforeCutAngleJudgments

Type: `segment[]`
Default: Several default segment objects
Required.

`beforeCutAngleJudgments` is an array of `segment` objects arranged in descending order of `threshold`, used for 'before cut' comparisons (0-70 scores).

### accuracyJudgments

Type: `segment[]`
Default: Several default segment objects
Required.

`accuracyJudgments` is an array of `segment` objects arranged in descending order of `threshold`, used for 'cut distance' comparisons (0-15 scores).

### afterCutAngleJudgments

Type: `segment[]`
Default: Several default segment objects
Required.

`afterCutAngleJudgments` is an array of `segment` objects arranged in descending order of `threshold`, used for 'after cut' comparisons (0-30 scores).
