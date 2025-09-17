#include "NatureKeeperUtils.h"

#include "IsometricCell.h"

TArray<ACell*> UNatureKeeperUtils::FindPath(ACell* StartCell, ACell* TargetCell)
{
	TArray<ACell*> ToSearchCells = { StartCell };
	TArray<ACell*> ProcessedCells;

	while (!ToSearchCells.IsEmpty()) {
		ACell* Current = ToSearchCells[0];
		for (auto Cell : ToSearchCells) 
			if (Cell->GetTotalCost() < Current->GetTotalCost()
				|| Cell->GetTotalCost() == Current->GetTotalCost()
				&& Cell->GetCostToTarget() < Current->GetCostToTarget()) Current = Cell;

		ProcessedCells.Add(Current);
		ToSearchCells.Remove(Current);
                

		if (Current == TargetCell) {
			ACell* CurrentPathCell = TargetCell;
			TArray<ACell*> ReversePath;
			while (CurrentPathCell != StartCell) {
				ReversePath.Add(CurrentPathCell);
				CurrentPathCell = CurrentPathCell->GetPathConnection();
			}

			TArray<ACell*> Path;
			for (int i = ReversePath.Num() - 1; i >= 0; i--)
				Path.Add(ReversePath[i]);
			
			return Path;
		}

		TArray<ACell*> FilteredNeighbours = FilterNeighbours(Current->Neighbours, ProcessedCells);
		
		for (auto Neighbour : FilteredNeighbours) {
			bool InSearch = ToSearchCells.Contains(Neighbour);

			int32 CostToNeighbour = Current->GetCostToStart() + Current->GetDistanceToOtherCell(Neighbour);

			if (!InSearch || CostToNeighbour < Neighbour->GetCostToStart()) {
				Neighbour->SetCostToStart(CostToNeighbour);
				Neighbour->SetPathConnection(Current);

				if (!InSearch) {
					Neighbour->SetCostToTarget(Neighbour->GetDistanceToOtherCell(TargetCell));
					ToSearchCells.Add(Neighbour);
				}
			}
		}
	}
	
	return TArray<ACell*>();
}

TArray<ACell*> UNatureKeeperUtils::FilterNeighbours(TArray<ACell*> Neighbours,
	TArray<ACell*> ProcessedCells)
{
	TArray<ACell*> FilteredNeighbours;

	for (int i = 0; i < Neighbours.Num(); i++)
	{
		if (Neighbours[i]->CellType == ECellType::ICT_Default && !ProcessedCells.Contains(Neighbours[i]))
			FilteredNeighbours.Add(Neighbours[i]);
	}

	return FilteredNeighbours;
}

float UNatureKeeperUtils::CalculatePerlinNoise2D(int XVertexIndex, int YVertexIndex,
                                                 float InNoiseScale, float InNoiseSeed)
{
	return FMath::PerlinNoise2D(FVector2D(XVertexIndex * InNoiseScale + InNoiseSeed,
		YVertexIndex * InNoiseScale + InNoiseSeed));
}

float UNatureKeeperUtils::CalculatePerlinNoise3D(FVector Point, float InNoiseScale, float InNoiseSeed)
{
	return FMath::PerlinNoise3D(Point * InNoiseScale + InNoiseSeed);
}