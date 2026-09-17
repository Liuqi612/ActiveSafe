
#pragma once

#include <utility>
#include <vector>

#include "container/strong_vector.h"
#include <absl/types/span.h>
#include "common/log.h"

#include "pncx_initializer.pb.h"
#include "initializer/geometry/geometry_graph.h"
#include "initializer/motion_form.h"
#include "initializer/motion_state.h"

namespace pnc_x {
namespace planning {
DECLARE_STRONG_VECTOR(MotionNode);
DECLARE_STRONG_VECTOR(MotionEdge);

struct MotionNode {
    MotionNodeIndex index;
    MotionState state;
    GeometryNodeIndex geom_index;
};

struct MotionEdge {
    MotionNodeIndex start;
    MotionNodeIndex end;
    const MotionForm *motion;
    MotionEdgeIndex prev_edge;
};

class MotionGraph {
 public:
    explicit MotionGraph(const GeometryGraph *geom_graph)
        : geometry_graph_(geom_graph) {}
    virtual int node_size() const = 0;
    virtual int edge_size() const = 0;
    virtual const MotionNode &GetMotionNode(MotionNodeIndex i) const = 0;
    virtual const MotionEdge &GetMotionEdge(MotionEdgeIndex i) const = 0;
    virtual MotionEdge *GetMutableMotionEdge(MotionEdgeIndex i) = 0;
    virtual absl::Span<const MotionEdgeIndex> GetOutgoingEdges(
        MotionNodeIndex i) const = 0;
    virtual MotionNodeIndex AddMotionNode(MotionState node,
                                          GeometryNodeIndex geom_index) = 0;
    virtual MotionEdgeIndex AddMotionEdge(MotionNodeIndex start_node_index,
                                          MotionNodeIndex end_node_index,
                                          const MotionForm *motion_form,
                                          GeometryNodeIndex end_geom_index,
                                          MotionEdgeIndex prev_edge) = 0;

    virtual const GeometryGraph *geometry_graph() const {
        return geometry_graph_;
    }

    virtual ~MotionGraph() {}

    virtual void ToProto(MotionGraphProto *proto) const = 0;

 protected:
    const GeometryGraph *geometry_graph_;
};

class XYTMotionGraph : public MotionGraph {
 public:
    explicit XYTMotionGraph(const GeometryGraph *geom_graph)
        : MotionGraph(geom_graph) {}

    int node_size() const override { return nodes_.size(); }
    int edge_size() const override { return edges_.size(); }

    const MotionNode &GetMotionNode(MotionNodeIndex i) const override {
        return nodes_[i];
    }
    const MotionEdge &GetMotionEdge(MotionEdgeIndex i) const override {
        return edges_[i];
    }
    MotionEdge *GetMutableMotionEdge(MotionEdgeIndex i) override {
        return &edges_[i];
    }

    absl::Span<const MotionEdgeIndex> GetOutgoingEdges(
        MotionNodeIndex i) const override {
        if (!XCHECK(outgoing_edges_.valid_index(i))) {
            return {};
        }
        return outgoing_edges_[i];
    }
    MotionNodeIndex AddMotionNode(MotionState node,
                                  GeometryNodeIndex geom_index) override;
    MotionEdgeIndex AddMotionEdge(MotionNodeIndex start_node_index,
                                  MotionNodeIndex end_node_index,
                                  const MotionForm *motion_form,
                                  GeometryNodeIndex end_geom_index,
                                  MotionEdgeIndex prev_edge) override;

    void ToProto(MotionGraphProto *proto) const override;

 private:
    std::vector<MotionEdgeIndex> *GetOrCreateOutgoingEdge(MotionNodeIndex i);

    MotionNodeVector<MotionNode> nodes_;
    MotionNodeVector<std::vector<MotionEdgeIndex>> outgoing_edges_;
    MotionEdgeVector<MotionEdge> edges_;
};

}  // namespace planning
}  // namespace pnc_x
