using UnrealBuildTool;
using System.Collections.Generic;

public class TrinomialTarget : TargetRules
{
	public TrinomialTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "Trinomial" } );
	}
}
