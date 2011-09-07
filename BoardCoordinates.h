#ifndef BoardCoordinates_h__
#define BoardCoordinates_h__

namespace puz {

	class BoardCoordinates {

	public:
		int Column;
		int Row;
		
		BoardCoordinates() : Column(0), Row(0) {}

		BoardCoordinates(int column, int row) : Column(column), Row(row) {}
		
		bool operator==(const BoardCoordinates& other) const {
			return Column == other.Column && Row == other.Row;
		}

		bool operator!=(const BoardCoordinates& other) const {
			return !(*this == other);
		}

		BoardCoordinates offset(int colOffset, int rowOffset) {		
			return BoardCoordinates(Column + colOffset, Row + rowOffset);
		}


	};


}


#endif // BoardCoordinates_h__