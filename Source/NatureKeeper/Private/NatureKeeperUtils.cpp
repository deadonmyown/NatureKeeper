#include "NatureKeeperUtils.h"

#include "IsometricCell.h"

TArray<AIsometricCell*> UNatureKeeperUtils::FindPath(AIsometricCell* StartCell, AIsometricCell* TargetCell)
{
	TArray<AIsometricCell*> ToSearchCells = { StartCell };
	TArray<AIsometricCell*> ProcessedCells;

	while (!ToSearchCells.IsEmpty()) {
		AIsometricCell* Current = ToSearchCells[0];
		for (auto Cell : ToSearchCells) 
			if (Cell->GetTotalCost() < Current->GetTotalCost()
				|| Cell->GetTotalCost() == Current->GetTotalCost()
				&& Cell->GetCostToTarget() < Current->GetCostToTarget()) Current = Cell;

		ProcessedCells.Add(Current);
		ToSearchCells.Remove(Current);
                

		if (Current == TargetCell) {
			AIsometricCell* CurrentPathCell = TargetCell;
			TArray<AIsometricCell*> ReversePath;
			while (CurrentPathCell != StartCell) {
				ReversePath.Add(CurrentPathCell);
				CurrentPathCell = CurrentPathCell->GetPathConnection();
			}

			TArray<AIsometricCell*> Path;
			for (int i = ReversePath.Num() - 1; i >= 0; i--)
				Path.Add(ReversePath[i]);
			
			return Path;
		}

		TArray<AIsometricCell*> FilteredNeighbours = FilterNeighbours(Current->Neighbours, ProcessedCells);
		
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
	
	return TArray<AIsometricCell*>();
}

TArray<AIsometricCell*> UNatureKeeperUtils::FilterNeighbours(TArray<AIsometricCell*> Neighbours,
	TArray<AIsometricCell*> ProcessedCells)
{
	TArray<AIsometricCell*> FilteredNeighbours;

	for (int i = 0; i < Neighbours.Num(); i++)
	{
		if (Neighbours[i]->CellType == EIsometricCellType::ICT_Default && !ProcessedCells.Contains(Neighbours[i]))
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