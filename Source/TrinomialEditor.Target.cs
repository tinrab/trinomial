using UnrealBuildTool;
using System.Collections.Generic;

public class TrinomialEditorTarget : TargetRules
{
	public TrinomialEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "Trinomial" } );
	}
}
